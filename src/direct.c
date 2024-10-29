#include <stdio.h>

#include "postgres.h"
#include "nodes/nodes.h"
#include "nodes/nodeFuncs.h"
#include "parser/parser.h"
#include "utils/memutils.h"
#include "mb/pg_wchar.h"
#include "nodes/pg_list.h"

#include "buf.h"

void parse_insert_stmt(InsertStmt *node) {
    printf("insert into %s.%s\n", 
            node->relation->schemaname, 
            node->relation->relname);
}

void parse_update_stmt(UpdateStmt *node) {
    printf("update %s.%s\n", 
            node->relation->schemaname, 
            node->relation->relname);
}

void parse_select_stmt(SelectStmt *node) {
    printf("select\n"); 
}

typedef bool (*match_node_func)(Node *);
typedef void (*node_func)(Node *);

void walk(Node *node, match_node_func match_node, node_func run) {
    if (node == NULL) return;

    if (match_node) {
        run(node);
    }

    if (IsA(node, List)) {
        ListCell *cell;
        foreach(cell, (List*)node) {
            Node *next = lfirst(cell);
            walk(node, match_node, run);
        }
        return;
    }

    if (IsA(node, InsertStmt)) {
        SelectStmt *stmt = (SelectStmt*)node;
        walk((Node*)stmt->targetList, match_node, run);
        walk((Node*)stmt->fromClause, match_node, run);
    }

    printf("NodeTag: %d\n", node->type);
}

typedef struct {
    int level;
} NodeContext;

bool walk_node(Node *node, NodeContext *ctx) 
{
    if (node == NULL) return false;

    // Print some space for each level
    for (int i=0; i < ctx->level; i++) printf("   ");

    // Process Node
    printf("NODE(%d): %d ", node->type, ctx->level);
    switch (node->type) {
#include "nodetags.h"
        default: break;
    }
    printf("\n");
    // End Process Node

    if (IsA(node, List)) {
        ctx->level++;
        List *list = (List*) node;
        ListCell *cell;
        foreach(cell, list) {
            Node *node = lfirst(cell);
            walk_node(node, ctx);
        }
        ctx->level--;
        return false;
    }

    bool result;
    ctx->level++;
    result = raw_expression_tree_walker(node, walk_node, ctx);
    ctx->level--;
    return result;
}

int main() {

	MemoryContext ctx = NULL;

	MemoryContextInit();
	SetDatabaseEncoding(PG_UTF8);

	Assert(CurrentMemoryContext == TopMemoryContext);
	ctx = AllocSetContextCreate(TopMemoryContext,
								"pg_query_direct",
								ALLOCSET_DEFAULT_SIZES);
	MemoryContextSwitchTo(ctx);

    char *query = file_read_string(stdin);

    List *tree = raw_parser(query, RAW_PARSE_DEFAULT);
	ListCell *cell;

    NodeContext node_ctx = {0};

    foreach(cell, tree) {
        RawStmt *raw = lfirst(cell);
        Node *node = raw->stmt;

        printf("-----------\n");
        printf("STATEMENT\n");
        bool result;
        /*result = raw_expression_tree_walker(node, find_node, ctx);*/
        result = walk_node(node, &node_ctx);
    }

    return 0;
}
