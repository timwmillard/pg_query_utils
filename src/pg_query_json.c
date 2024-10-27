#include <pg_query.h>
#include "protobuf/pg_query.pb-c.h"

#include <stdio.h>
#include <stdlib.h>

#define INIT_BUFFER_SIZE 256

int main() {
    PgQueryParseResult result;

    char *query;
    size_t buf_size = INIT_BUFFER_SIZE;
    
    query = malloc(buf_size);
    if (query == NULL) {
        perror("unable to allocate query buffer");
        return 1;
    }

    size_t index = 0;
    char c;
    while ((c = fgetc(stdin)) != EOF) {
        if (index + 1 > buf_size) {
            buf_size *= 2;
            query = realloc(query, buf_size);
            if (query == NULL) {
                perror("unable to increase query buffer");
                return 1;
            }
        }
        query[index++] = c;
    }
    query[index] = '\0';

    result = pg_query_parse(query);

    printf("%s\n", result.parse_tree);

    pg_query_free_parse_result(result);

    return 0;
}

