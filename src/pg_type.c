#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

char** get_type_names_from_oids_bulk(PGconn *conn, Oid *oids, int oid_count) {
    // Create a parameterized query string
    char query[1024] = "SELECT typname FROM pg_type WHERE oid = ANY($1)";
    
    // Convert Oids array to string representation for PQexecParams
    char *oids_str = malloc(oid_count * 12);  // Each Oid can be up to 10 digits plus commas
    if (!oids_str) return NULL;
    oids_str[0] = '\0';

    for (int i = 0; i < oid_count; i++) {
        char temp[12];
        snprintf(temp, sizeof(temp), "%u,", oids[i]);
        strcat(oids_str, temp);
    }
    oids_str[strlen(oids_str) - 1] = '\0';  // Remove last comma

    const char *paramValues[1] = { oids_str };

    PGresult *res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);
    free(oids_str);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return NULL;
    }

    int num_results = PQntuples(res);
    char **type_names = malloc(num_results * sizeof(char *));
    if (!type_names) {
        PQclear(res);
        return NULL;
    }

    for (int i = 0; i < num_results; i++) {
        type_names[i] = strdup(PQgetvalue(res, i, 0));
    }

    PQclear(res);
    return type_names;
}

