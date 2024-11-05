#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int cap;
    int len;
} arrayHeader;


static inline arrayHeader *array_grow(arrayHeader *list, size_t index, size_t item_size) {
    // Alloc array
    if (list == NULL) {
        const size_t cap = 32;
        size_t size = item_size + item_size * cap;
        list = malloc(size);
        if (!list) {
            perror("array out of memory");
            return list;
        }
        memset(list, 0, size);
        list->cap = cap;
    }

    // Set array len
    if (index + 1 > list->len)
        list->len = index + 1;

    // Grow array
    if (list->len > list->cap) {
        list->cap = list->cap * 2; 
        size_t size = item_size + item_size * list->cap;
        list = realloc(list, size);
        if (!list) {
            perror("array out of memory");
            return list;
        }
    }
    return list;
}

#define ARRAY_LEN(l) ((l) ? (l)->len : 0)
#define ARRAY_CAP(l) ((l) ? (l)->cap : 0)

#define ARRAY(name, T) typedef struct { \
    int cap; \
    int len; \
    T items[]; \
} name; \
name *name##_insert(name *list, size_t index, T data) { \
    list = (name*) array_grow((arrayHeader*)list, index, sizeof(T)); \
    list->items[index] = data; \
    return list; \
} \
name *name##_append(name *list, T data) { \
    list = (name*) array_grow((arrayHeader*)list, ARRAY_LEN(list), sizeof(T)); \
    list->items[list->len] = data; \
    return list; \
}

ARRAY(CharList, char)
ARRAY(IntList, int)
ARRAY(FloatList, float)
ARRAY(DoubleList, double)
ARRAY(StringList, char*)


#endif // ARRAY_H

