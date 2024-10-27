
CFLAGS += -Isrc/vendor/libpg_query/ -Isrc/vendor/libpg_query/vendor/
LDFLAGS += -Lsrc/vendor/libpg_query/ -lpg_query

.PHONY: all

all: pg_query_args pg_query_json

pg_query_json: src/pg_query_json.c src/vendor/libpg_query/libpg_query.a
	clang $(CFLAGS) $(LDFLAGS) src/pg_query_json.c -o pg_query_json

pg_query_args: src/main.c src/vendor/libpg_query/libpg_query.a
	clang $(CFLAGS) $(LDFLAGS) src/main.c -o pg_query_args

src/vendor/libpg_query/libpg_query.a:
	cd src/vendor/libpg_query && \
	make

