/*
 * pg_query_prepare
 * 
 *
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

struct options 
{
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
            printf("fingerprint=%s\n", fingerprint_result.fingerprint_str);
        }
    }

    return 0;
}

