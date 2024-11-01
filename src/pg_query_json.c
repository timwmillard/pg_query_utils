#include <stdio.h>

#include <pg_query.h>

#include "buf.h"

int main() {
    PgQueryParseResult result;

    char *query = file_read_string(stdin);

    result = pg_query_parse(query);
    if (result.error) {
        fprintf(stderr, "error: %s at pos:%d\n", 
                result.error->message, 
                result.error->cursorpos);
        return 1;
    }
    printf("%s\n", result.parse_tree);

    pg_query_free_parse_result(result);

    return 0;
}

