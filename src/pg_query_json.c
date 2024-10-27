#include <stdio.h>
#include <stdlib.h>

#include <pg_query.h>

#define INIT_BUFFER_SIZE 256

char *load_buffer(FILE *fd) {
    char *buf;
    size_t buf_size = INIT_BUFFER_SIZE;
    
    buf = malloc(buf_size);
    if (buf == NULL) {
        perror("unable to allocate buf buffer");
        return NULL;
    }

    size_t index = 0;
    char c;
    while ((c = fgetc(stdin)) != EOF) {
        if (index + 1 > buf_size) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
            if (buf == NULL) {
                perror("unable to increase buf buffer");
                exit(1);
            }
        }
        buf[index++] = c;
    }
    buf[index] = '\0';
    return buf;
}

int main() {
    PgQueryParseResult result;

    char *query = load_buffer(stdin);

    result = pg_query_parse(query);

    printf("%s\n", result.parse_tree);

    pg_query_free_parse_result(result);

    return 0;
}

