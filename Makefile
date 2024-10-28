
CFLAGS += -Isrc/vendor/libpg_query/ -Isrc/vendor/libpg_query/vendor/
LDFLAGS += -Lsrc/vendor/libpg_query/ -lpg_query

.PHONY: all

all: pg_query_args pg_query_json pg_query_fingerprint

direct: src/direct.c
	clang -g -Isrc/vendor/libpg_query/src/postgres/include/ $(LDFLAGS) \
		-o direct \
		src/direct.c

pg_query_json: src/pg_query_json.c src/vendor/libpg_query/libpg_query.a
	clang $(CFLAGS) $(LDFLAGS) src/pg_query_json.c -o pg_query_json

pg_query_fingerprint: src/pg_query_fingerprint.c src/vendor/libpg_query/libpg_query.a
	clang $(CFLAGS) $(LDFLAGS) src/pg_query_fingerprint.c -o pg_query_fingerprint

pg_query_args: src/main.c src/vendor/libpg_query/libpg_query.a
	clang $(CFLAGS) $(LDFLAGS) src/main.c -o pg_query_args

src/vendor/libpg_query/libpg_query.a:
	cd src/vendor/libpg_query && \
	make


# libpq dependencies
PKG_CONFIG_PATH="/opt/homebrew/opt/libpq/lib/pkgconfig"

CFLAGS+=$(shell pkg-config --cflags libpq)
LDFLAGS+=$(shell pkg-config --libs libpq)

pg_describe_query: src/pg_describe_query.c src/vendor/libpg_query/libpg_query.a
	clang $(CFLAGS) $(LDFLAGS) src/pg_describe_query.c -o pg_describe_query

