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
#include "parser/parser.h"
#include "utils/memutils.h"
#include "mb/pg_wchar.h"
#include "nodes/pg_list.h"


#include "pg_query.h"
#include "buf.h"

#define VERSION "0.0.1"

static void version(void)
{
	puts("pg_query_prepare " VERSION);
}

void usage()
{
	printf("pg_query_prepard is a utility for anaylsing prepare statments.\n\n");
	printf("Usage:\n");
	printf("  pg_query_prepare [OPTION]...\n\n");

	printf("\nOptions:\n");
	printf("  -?, --help               show this help, then exit\n");
	printf("  -V, --version            output version information, then exit\n");
	printf("  -c, --command=COMMAND    run only single command (SQL)\n");
	printf("  -f, --file=FILENAME      read from file instead of stdin\n");
	printf("  -p, --fingerprint        calculate each queries fingerprint\n");
}

struct options 
{
    bool fingerprint;
    FILE *input;
    char *query;
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
        { "fingerprint", no_argument,       NULL, 'p' },
        { "version",     no_argument,       NULL, 'V' },
        { NULL,          0,                 NULL,  0  }
    };

    while ((ch = getopt_long(argc, argv, "c:f:pV?", longopts, NULL)) != -1) {
        switch (ch) {
            case 'c': 
                opts->query = optarg;
                break;
            case 'p':
                opts->fingerprint = true;
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
                opts->input = fd;
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
    opts.input = stdin;

    // Parse options
    parse_options(argc, argv, &opts);

    // Read query from input
    char *query;
    if (opts.query == NULL)
        query = file_read_string(opts.input);
    else
        query = opts.query;

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

        if (opts.fingerprint) {
            PgQueryFingerprintResult fingerprint_result = pg_query_fingerprint_from_tree(raw);
            if (fingerprint_result.error) {
                fprintf(stderr, "error: %s at pos:%d\n", 
                        fingerprint_result.error->message, 
                        fingerprint_result.error->cursorpos);
                return 1;
            }
            printf("fingerprint: %s\n", fingerprint_result.fingerprint_str);
        }
    }

    return 0;
}

