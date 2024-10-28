#include <pg_query.h>
#include "protobuf/pg_query.pb-c.h"

#include <stdio.h>
#include <stdlib.h>

#define INIT_BUFFER_SIZE 256

int main() {
    PgQueryScanResult result;
    PgQuery__ScanResult *scan_result;
    PgQuery__ScanToken *scan_token;

    const ProtobufCEnumValue *token_kind;
    const ProtobufCEnumValue *keyword_kind;

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

    result = pg_query_scan(query);

    scan_result = pg_query__scan_result__unpack(NULL, result.pbuf.len, (void*) result.pbuf.data);
    printf("  version: %d, tokens: %ld, size: %ld\n", scan_result->version, scan_result->n_tokens, result.pbuf.len);
    for (size_t i = 0; i < scan_result->n_tokens; i++) {
        scan_token = scan_result->tokens[i];
        token_kind = protobuf_c_enum_descriptor_get_value(&pg_query__token__descriptor, scan_token->token);
        /*token_kind = protobuf_c_enum_descriptor_get_value(&pg_query__token__descriptor, scan_token->token);*/
        /*keyword_kind = protobuf_c_enum_descriptor_get_value(&pg_query__keyword_kind__descriptor, scan_token->keyword_kind);*/
        /*printf("  \"%.*s\" = [ %d, %d, %s, %s ]\n", scan_token->end - scan_token->start, &(input[scan_token->start]), scan_token->start, scan_token->end, token_kind->name, keyword_kind->name);*/
    }


    pg_query_free_scan_result(result);

    return 0;
}

