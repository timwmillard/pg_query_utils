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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include "libpq-fe.h"

#include "buf.h"

#define VERSION "0.0.1"

typedef struct {
    int number;
    char *name;
    char *type;
    Oid type_oid;
} ParamVar;

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

static void version(void)
{
	puts("pg_describe_query " VERSION);
}

void usage()
{
	printf("pg_describe_query is a utility for describing a PostgreSQL query.\n\n");
	printf("Usage:\n");
	printf("  pg_describe_query [OPTION]... [DBNAME [USERNAME]]\n\n");

	printf("General options:\n");
	printf("  -c, --command=COMMAND    run only single command (SQL or internal) and exit\n");
	printf("  -d, --dbname=DBNAME      database name to connect to\n");
	printf("  -f, --file=FILENAME      execute commands from file, then exit\n");
	printf("  -V, --version            output version information, then exit\n");
	printf("  -?, --help               show this help, then exit\n");

	printf("\nConnection options:\n");
	printf("  -h, --host=HOSTNAME      database server host or socket directory\n");
	printf("  -p, --port=PORT          database server port\n");
	printf("  -U, --username=USERNAME  database user name\n");
	printf("  -w, --no-password        never prompt for password\n");
	printf("  -W, --password           force password prompt (should happen automatically)\n");
}

struct opts 
{
	char	   *dbname;
	char	   *host;
	char	   *port;
	char	   *username;

    FILE *input;
};

static void parse_options(int argc, char *argv[], struct opts *options) 
{
    int ch;
    FILE *fd;

    /* options descriptor */
    static struct option longopts[] = {
		{ "help",        no_argument,       NULL, '?' },
        { "command",     required_argument, NULL, 'c' },
        { "dbname",      required_argument, NULL, 'd' },
        { "file",        required_argument, NULL, 'f' },
        { "host",        required_argument, NULL, 'h' },
        { "no-password", no_argument,       NULL, 'w' },
        { "password",    no_argument,       NULL, 'W' },
        { "port",        required_argument, NULL, 'p' },
        { "username",    required_argument, NULL, 'U' },
        { "version",     no_argument,       NULL, 'V' },
        { NULL,          0,                 NULL,  0  }
    };

    while ((ch = getopt_long(argc, argv, "c:d:f:Vh:p:U:wW?", longopts, NULL)) != -1) {
        switch (ch) {
            case 'c': break;
            case 'd': 
                printf("database=%s\n", optarg);
                break;
            case 'V':
                version();
                exit(0);
            case 'f':
                fd = fopen(optarg, "r");
                if (fd == NULL) {
                    fprintf(stderr, "error opening file: %s\n", optarg);
					exit(1);
                }
                options->input = fd;
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
                fprintf(stderr, "Try: pg_describe_query --help\n");
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;
}

static struct opts options;

int main(int argc, char *argv[]) 
{
    options.input = stdin;

    parse_options(argc, argv, &options);

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */

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


  ParamVar *data = malloc(sizeof(ParamVar) * PQnparams(desc_prep_res));

  for (int i = 0; i < PQnparams(desc_prep_res); i++) {
    Oid param_type = PQparamtype(desc_prep_res, i);
    printf("Param type=%d\n", param_type);
    data[i] = (ParamVar){
        .number = i + 1,
        .type_oid = param_type,
    };
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
