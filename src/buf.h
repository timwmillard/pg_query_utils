#ifndef BUF_H
#define BUF_H

#include <stdio.h>
#include <stdlib.h>

char *file_read_append_string(char *str, FILE *fd) {
    char *buf;
    size_t buf_size = 256; // inital buffer size
    
    buf = malloc(buf_size);
    if (buf == NULL) {
        perror("unable to allocate buf buffer");
        return NULL;
    }

    size_t index = 0;
    char c;
    while ((c = fgetc(stdin)) != EOF) {
        if (index + 1 > buf_size) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
            if (buf == NULL) {
                perror("unable to increase buf buffer");
                exit(1);
            }
        }
        buf[index++] = c;
    }
    buf[index] = '\0';
    return buf;
}

char *file_read_string(FILE *fd) {
    char *buf;
    size_t buf_size = 256; // inital buffer size
    
    buf = malloc(buf_size);
    if (buf == NULL) {
        perror("unable to allocate buf buffer");
        return NULL;
    }

    size_t index = 0;
    char c;
    while ((c = fgetc(fd)) != EOF) {
        if (index + 1 > buf_size) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
            if (buf == NULL) {
                perror("unable to increase buf buffer");
                exit(1);
            }
        }
        buf[index++] = c;
    }
    buf[index] = '\0';
    return buf;
}

#endif

