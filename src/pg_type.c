#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

char** get_type_names_from_oids_bulk(PGconn *conn, Oid *oids, int oid_count) {
    // Query using the ANY operator to match an array of Oids
    const char *query = "SELECT typname FROM pg_type WHERE oid = ANY($1)";

    // Calculate the total size needed for the binary array
    int paramLength = oid_count * sizeof(Oid);
    char *paramValues[1] = { (char *)oids };  // Pass the array directly
    const int paramFormats[1] = { 1 };         // Binary format
    const int paramLengths[1] = { paramLength };
    Oid paramTypes[1] = { INT4ARRAYOID };      // Array of 32-bit integers

    PGresult *res = PQexecParams(conn, query, 1, paramTypes, (const char **)paramValues, paramLengths, paramFormats, 0);

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
