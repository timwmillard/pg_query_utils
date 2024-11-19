/*
 * pg_query_prepare.c
 *    Utility program to analyse a query and return number of params.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

#include "postgres.h"
#include "nodes/parsenodes.h"
#include "nodes/nodeFuncs.h"
#include "nodes/pg_list.h"

#include "pg_query.h"
#include "buf.h"
#include "ds.h"

#define VERSION "0.0.1"

static void version(void)
{
    printf("pg_query_prepare " VERSION "\n\n");

    printf("PostgreSQL " PG_VERSION "\n");
}

void usage()
{
    printf("pg_query_prepare is a utility for analysing prepare statements.\n\n");
    printf("Usage:\n");
    printf("  pg_query_prepare [OPTION]...\n");

    printf("\nOptions:\n");
    printf("  -?, --help               show this help, then exit\n");
    printf("  -V, --version            output version information\n");
    printf("  -c, --command=COMMAND    run only single command (SQL)\n");
    printf("  -f, --file=FILENAME      read from file instead of stdin\n");
    printf("  -d, --details            output query details\n");
}

struct options {
    char *command;
    char *file;
    bool details;
};

static void parse_options(int argc, char *argv[], struct options *opts) 
{
    int ch;
    FILE *fd;

    /* options descriptor */
    static struct option longopts[] = {
        { "help",        no_argument,       NULL, '?' },
        { "command",     required_argument, NULL, 'c' },
        { "file",        required_argument, NULL, 'f' },
        { "details",     no_argument,       NULL, 'd' },
        { "version",     no_argument,       NULL, 'V' },
        { NULL,          0,                 NULL,  0  }
    };

    while ((ch = getopt_long(argc, argv, "c:f:dV?", longopts, NULL)) != -1) {
        switch (ch) {
            case 'c':
                opts->command = optarg;
                break;
            case 'd':
                opts->details = true;
                break;
            case 'V':
                version();
                exit(0);
            case 'f':
                opts->file = optarg;
                break;
            case '?':
                if (optind <= argc &&
                    (strcmp(argv[optind - 1], "-?") == 0 ||
                    strcmp(argv[optind - 1], "--help") == 0)) {
                    usage();
                    exit(0);
                }
                // no break, fallthrough to default
            default:
                fprintf(stderr, "Try: pg_query_prepare --help\n");
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;
}

typedef struct {
    int number;
    char *name;
} QueryParam;

ARRAY(QueryParamList, QueryParam);

QueryParamList *add_query_param(QueryParamList *list, int number, char *name) {
    if (ARRAY_LEN(list) > number) {
        QueryParam param = list->items[number - 1];
        if (param.name != NULL && name != NULL) {
            size_t len = strlen(param.name) + strlen(name) + 2; // '&' and '\0'
            char *new_name = malloc(len);
            strcpy(new_name, param.name);
            strcat(new_name, "&");
            strcat(new_name, name);
            name = new_name;
        }
    }
    return QueryParamList_insert(list, number - 1, (QueryParam){number, name});
}

StringList *add_pg_query_prepare_col(StringList *list, int number, char *name) {
    return StringList_insert(list, number - 1,  name);
}

typedef struct {
    int level;
    int node_count;

    Node *parent;

    QueryParamList *params;
    char *last_name;
} NodeContext;


bool walk_node(Node *node, NodeContext *ctx)
{
    ctx->node_count++;
    if (node == NULL) return false;

    /********************/
/*    // Print some space for each level*/
/*    for (int i=0; i < ctx->level; i++) printf(" ");*/
/**/
/*    // Process Node*/
/*    switch (node->type) {*/
/*#include "nodetags.h"*/
/*        default: break;*/
/*    }*/
/*    printf("(%d)", node->type);*/
/*    // printf(" level=%d", ctx->level);*/
/*    if (ctx->parent != NULL) {*/
/*        printf(" parent=%d", ctx->parent->type);*/
/*    }*/
/*    printf("\n");*/
/*    // End Process Node*/
    /********************/

    // found on INSERT query
    if (IsA(node, InsertStmt)) {
        ListCell *cell;
        InsertStmt *insert = (InsertStmt*)node;

        int col_names_len = 0;
        char **col_names;
        // Columns
        col_names_len = list_length(insert->cols);
        col_names = malloc(sizeof(char*) * col_names_len);
        int i = 0;
        foreach(cell, insert->cols) {
            Node *node = lfirst(cell);
            if (IsA(node, ResTarget)) {
                ResTarget *res = (ResTarget*)node;
                col_names[i] = res->name;
            } else if (walk_node(node, ctx)) {
                free(col_names);
                return true;
            }
            i++;
        }

        if (insert->selectStmt == NULL) goto insert_cleanup;
        SelectStmt *select = (SelectStmt*)insert->selectStmt;
        foreach(cell, select->valuesLists) {
            Node *node = lfirst(cell);
            /*if (!IsA(node, List)) {*/
            /*    if (walk_node(node, ctx))*/
            /*            return true;*/
            /*    continue;*/
            /*}*/
            List *values = (List*)node;
            int i = 0;
            foreach(cell, values) {
                Node *node = lfirst(cell);
                if (IsA(node, ParamRef)) {
                    ParamRef *ref = (ParamRef*)node;
                    ctx->params = add_query_param(ctx->params, ref->number, col_names[i]);
                } 
                /*else if (walk_node(node, ctx))*/
                /*    return true;*/
                i++;
            }
        }

    insert_cleanup:
        free(col_names);

        return false;
    }

    if (IsA(node, ParamRef)) {
        ParamRef *ref = (ParamRef*)node;
        char *param_name = NULL;

        // found on WHERE clause
        if (IsA(ctx->parent, A_Expr)) {
            A_Expr *expr = (A_Expr*)ctx->parent;
            if (IsA(expr->lexpr, ColumnRef) && IsA(expr->rexpr, ParamRef)) {
                ColumnRef *col = (ColumnRef*)expr->lexpr;
                ParamRef *ref = (ParamRef*)expr->rexpr;

                ListCell *cell;
                foreach(cell, col->fields) {
                    Node *node = lfirst(cell);
                    if (IsA(node, String)) {
                        String *name = (String*)node;
                        param_name = name->sval;
                    }
                }
            }
        }
            // found on UPDATE query
        if (IsA(ctx->parent, ResTarget)) {
            ResTarget *res = (ResTarget*)ctx->parent;
            if (res->val != NULL && IsA(res->val, ParamRef)) {
                param_name = res->name;
            }
        }

        ctx->params = add_query_param(ctx->params, ref->number, param_name);
        return false;
    }
    
    if (IsA(node, List)) {
        ctx->level++;
        List *list = (List*) node;
        ListCell *cell;
        foreach(cell, list) {
            Node *item = lfirst(cell);
            Node *parent = ctx->parent;
            ctx->parent = node;
            if (walk_node(item, ctx))
                return true;
            ctx->parent = parent;
        }
        ctx->level--;
        return false;
    }


    bool result;
    ctx->level++;
    Node *parent = ctx->parent;
    ctx->parent = node;
    result = raw_expression_tree_walker(node, walk_node, ctx);
    ctx->parent = parent;
    ctx->level--;
    return result;
}

int main(int argc, char *argv[])
{
    // Set defaults
    struct options opts = {0};

    // Parse options
    parse_options(argc, argv, &opts);

    // Read query from input
    char *query;
    if (opts.command != NULL) {
        query = opts.command;
    } else if (opts.file != NULL) {
        FILE *fd = fopen(opts.file, "r");
        if (fd == NULL) {
            printf("error opening file %s\n", opts.file);
            perror("error opening file");
            exit(1);
        }
        query = file_read_string(fd);
    } else {
        query = file_read_string(stdin);
    }

    PgQueryParsetreeResult result = pg_query_parsetree(query);
    if (result.error) {
        fprintf(stderr, "error: %s at pos:%d\n",
                result.error->message,
                result.error->cursorpos);
        return 1;
    }

    List *tree = result.tree;
    ListCell *cell;
    foreach(cell, tree) {
        RawStmt *raw = lfirst(cell);

        if (opts.details) {
            PgQueryFingerprintResult fingerprint_result = pg_query_fingerprint_from_tree(raw);
            if (fingerprint_result.error) {
                fprintf(stderr, "error: %s at pos:%d\n",
                        fingerprint_result.error->message,
                        fingerprint_result.error->cursorpos);
                return 1;
            }
            printf("query=%s", fingerprint_result.fingerprint_str);

            Node *node = raw->stmt;

            NodeContext node_ctx = {0};
            /*printf("------------\n");*/
            walk_node(node, &node_ctx);

            if (ARRAY_LEN(node_ctx.params) > 0)
                printf(" params=");

            for (int i = 0; i < ARRAY_LEN(node_ctx.params); i++) {
                QueryParam param = node_ctx.params->items[i];
                if (param.number == 0) continue;
                printf("%d", param.number);
                if (param.name != NULL) {
                    printf(":%s", param.name);
                }
                if (i + 1 < ARRAY_LEN(node_ctx.params))
                    printf(",");
            }
            printf("\n");
        }
    }
    if (opts.details) return 0;

    PgQuerySplitResult split_result = pg_query_split_with_parser(query);
    if (split_result.error) {
        fprintf(stderr, "error: %s at pos:%d\n",
                split_result.error->message,
                split_result.error->cursorpos);
        return 1;
    }

    for (int i=0; i < split_result.n_stmts; i++) {
        PgQuerySplitStmt *stmt = split_result.stmts[i];
        char *start = &query[stmt->stmt_location];
        int len = stmt->stmt_len;
        while (isspace(*start)) {
            start++;
            len--;
        }
        char *end = start + len - 1;
        while (isspace(*end)) {
            end--;
            len--;
        }
        printf("-- statement %d\nPREPARE pg_query_prepare_%d AS %.*s;\n", i, i, len, start);
    }

    return 0;
}

