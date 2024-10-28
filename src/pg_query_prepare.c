#include <stdio.h>
#include "buf.h"

int main() {

    char *query = file_read_string(stdin);

    printf("query = %s\n", query);
    return 0;
}

