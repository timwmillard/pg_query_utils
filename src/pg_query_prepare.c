/*
 * pg_query_prepare
 * 
 *
 *
 */
#include <stdio.h>
#include <string.h>
#include <getopt.h>

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
	printf("  -c, --command=COMMAND    run only single command (SQL)\n");
	printf("  -f, --file=FILENAME      read from file instead of stdin\n");
	printf("  -V, --version            output version information, then exit\n");
	printf("  -?, --help               show this help, then exit\n");
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
        { "file",        required_argument, NULL, 'f' },
        { "version",     no_argument,       NULL, 'V' },
        { NULL,          0,                 NULL,  0  }
    };

    while ((ch = getopt_long(argc, argv, "c:f:V?", longopts, NULL)) != -1) {
        switch (ch) {
            case 'c': break;
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
                fprintf(stderr, "Try: pg_query_prepare --help\n");
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;
}

static struct opts options;

int main(int argc, char *argv[]) {

    // Set defaults
    options.input = stdin;

    parse_options(argc, argv, &options);

    char *query = file_read_string(options.input);

    printf("query = %s\n", query);
    return 0;
}

