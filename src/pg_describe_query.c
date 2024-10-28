/*
 * pg_describe_query
 *
 * results
 *    number   -- $1, $2 etc
 *    name     -- id, or name
 *    type     -- text or integer
 *    type_oid -- 23
 *
 *
 *
 *
 *
 */

#include "libpq-fe.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_result(PGresult *result) {

  PQprintOpt printOpts = {
      .header = true,    // print output field headings and row count
      .align = true,     // fill align the fields
      .standard = true,  // old brain dead format
      .html3 = false,    // output html tables
      .expanded = false, // expand tables
      .pager = false,    // use pager for output if needed
      .fieldSep = "|",   // field separator
      .tableOpt = NULL,  // insert to HTML <table ...>
      .caption = NULL,   // HTML <caption>
      .fieldName = NULL, // null terminated array of replacement field names
  };
  PQprint(stdout, result, &printOpts);
}

static void exit_nicely(PGconn *conn) {
  PQfinish(conn);
  exit(1);
}

int main(int argc, char **argv) {

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  const char *prepare;
  if (argc > 1)
    prepare = argv[1];
  else
    prepare = "get_users";

  char *conninfo = getenv("DATABASE_URL");
  if (conninfo == NULL) {
      conninfo = "";
    /* fprintf(stderr, "Missing DATABASE_URL env variable\n"); */
    /* exit(1); */
  }

  /* Make a connection to the database */
  PGconn *conn;
  conn = PQconnectdb(conninfo);

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "%s", PQerrorMessage(conn));
    exit_nicely(conn);
  }

  /* PGresult *result; */
  /* result = */
  /*     PQexec(conn, "select * from users"); */

  /* PGresult *prepare_res = */
  /*     PQprepare(conn, "get_users", "select * from users", 0, NULL); */

  /* if (PQresultStatus(prepare_res) != PGRES_COMMAND_OK) { */
  /*   fprintf(stderr, "query failed: %s", PQerrorMessage(conn)); */
  /*   PQclear(prepare_res); */
  /*   exit_nicely(conn); */
  /* } */

  /* print_result(prepare_res); */
  /* PQclear(prepare_res); */

  /* PGresult *exec_res = PQexecPrepared(conn, "get_users", 0, NULL, NULL, NULL,
   */
  /*                                     0); // 0 text format, 1 binary format
   */
  /* if (PQresultStatus(exec_res) != PGRES_TUPLES_OK) { */
  /*   fprintf(stderr, "query failed: %s", PQerrorMessage(conn)); */
  /*   PQclear(exec_res); */
  /*   exit_nicely(conn); */
  /* } */
  /* print_result(exec_res); */
  /* PQclear(exec_res); */

  PGresult *exec_res =
      // PQexec(conn, "prepare \"get_users\" as select * from users where id = $1 and name = $2::varchar");
      PQexec(conn, "prepare \"get_users\" as insert into users (id, name) values ($1, $2) returning *;");
  if (PQresultStatus(exec_res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "query failed: %s", PQerrorMessage(conn));
    PQclear(exec_res);
    exit_nicely(conn);
  }

  PGresult *desc_prep_res = PQdescribePrepared(conn, "get_users");
  if (PQresultStatus(desc_prep_res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "query failed: %s", PQerrorMessage(conn));
    PQclear(desc_prep_res);
    exit_nicely(conn);
  }
  print_result(desc_prep_res);

  for (int i = 0; i < PQnparams(desc_prep_res); i++) {
    Oid param_type = PQparamtype(desc_prep_res, i);
    printf("Param type=%d\n", param_type);
    // select <oid>::regtype;
  }

  for (int i = 0; i < PQnfields(desc_prep_res); i++) {
    char *field_name = PQfname(desc_prep_res, i);
    Oid field_type = PQftype(desc_prep_res, i);
    printf("Field name=%s, type=%d\n", field_name, field_type);
  }

  PQclear(desc_prep_res);

  return 0;
}
