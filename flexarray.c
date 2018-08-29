#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"


struct flexarrayrec {
    int capacity;
    int num_keys;
    char *key;
};


flexarray flexarray_new() {
    flexarray f = emalloc(sizeof * f);
    f->capacity = 1;
    f->num_keys = 0;
    f->key = emalloc(f->capacity * sizeof f->key[0]);
    return f;
}


void flexarray_append(flexarray f, char c) {
    if (f->num_keys == f->capacity) {
        f->capacity += 1;
        f->key = erealloc(f->key, f->capacity * sizeof f->key[0]);
    }
    f->key[f->num_keys++] = c;
}


void flexarray_print(flexarray f) {
    int i;
    for (i = 0; i < f->num_keys; i++) {
        printf("%c ", f->key[i]);
    }
}


void flexarray_free(flexarray f) {
    free(f->key);
    free(f);
}
