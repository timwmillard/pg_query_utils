/*
 * pg_query_prepare.c
 *    Utility program to analyse a query and return number of params.
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include "postgres.h"
#include "nodes/nodeFuncs.h"
#include "nodes/pg_list.h"

#include "pg_query.h"
#include "buf.h"

#define VERSION "0.0.1"

static void version(void)
{
	printf("pg_query_prepare " VERSION "\n\n");

	printf("PostgreSQL " PG_VERSION "\n");
}

void usage()
{
	printf("pg_query_prepard is a utility for anaylsing prepare statments.\n\n");
	printf("Usage:\n");
	printf("  pg_query_prepare [OPTION]...\n\n");

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
} PgQueryPrepareParam;

typedef struct {
    char *fingerprint;
    PgQueryPrepareParam *params;
} PgQueryPrepareStatement;

typedef struct {
    int level;
    int node_count;

    List *params;
} NodeContext;

int	list_PgQueryPrepareParam_cmp(const ListCell *c1, const ListCell *c2)
{
    PgQueryPrepareParam *p1 = lfirst(c1);
    PgQueryPrepareParam *p2 = lfirst(c2);
    int a = p1->number;
    int b = p2->number;

	return (a > b) - (a < b);
}

bool walk_node(Node *node, NodeContext *ctx) 
{
    ctx->node_count++;
    if (node == NULL) return false;

    if (IsA(node, List)) {
        ctx->level++;
        List *list = (List*) node;
        ListCell *cell;
        foreach(cell, list) {
            Node *node = lfirst(cell);
            if (walk_node(node, ctx))
                return true;
        }
        ctx->level--;
        return false;
    }

    if (IsA(node, ParamRef)) {
        ParamRef *ref = (ParamRef*)node;
        PgQueryPrepareParam *param = malloc(sizeof(PgQueryPrepareParam));
        param->number = ref->number;
        ctx->params = lappend(ctx->params, param);
    }

    bool result;
    ctx->level++;
    result = raw_expression_tree_walker(node, walk_node, ctx);
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
            walk_node(node, &node_ctx);

            if (list_length(node_ctx.params) > 0)
                printf(" params=");

            list_sort(node_ctx.params, list_PgQueryPrepareParam_cmp);

            ListCell *param_cell;
            int i = 0;
            foreach(param_cell, node_ctx.params) {
                i++;
                PgQueryPrepareParam *param = lfirst(param_cell);
                printf("%d", param->number);
                if (i < list_length(node_ctx.params))
                    printf(",");
            }
            printf("\n");
        }
    }

    return 0;
}

