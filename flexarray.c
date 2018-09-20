#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"



/* A flexable array ADT used for reading & storing charachters read from
 * the .csv files mnist_train & mnist_test. A flexable array structure is
 * required because the input values can range for 0 - 255, so they will vary
 * in how many digits they contain. If we just allocated enough memory for
 * 3 digits for all of them then we wouyld need to initialize the charachters
 * to zero and the atoi function would return 300 in place if 3.
 */
struct flexarrayrec {
    int capacity;
    int key_index;
    char *key;
};


/* Allocates memory for the flexarray and initializes its values.
 * @return: f - the new flexarray.
 */
flexarray flexarray_new() {
    flexarray f = emalloc(sizeof * f);
    f->capacity = 0;
    f->key_index = 0;
    f->key = emalloc(f->capacity * sizeof f->key[0]);
    return f;
}


/* Increments the capacity and reallocates memory, then inserts the new value.
 * @param: f - the flexarray.
 * @param: c - the charachter.
 */
void flexarray_append(flexarray f, char c) {
    f->capacity += 1;
    f->key = erealloc(f->key, f->capacity * sizeof f->key[0]);
    f->key[f->key_index++] = c;
}


/* Prints the flexarrays key.
 * @param: the flexarray.
 */
void flexarray_print(flexarray f) {
    printf("%s\n", f->key);
}


/* Deallocates memory associated with the flexarray.
 * @param: f - the flexarray.
 */
void flexarray_free(flexarray f) {
    free(f->key);
    free(f);
}


/* returns the integer representation of the flexarrays key.
 * @param: f - the flexarray.
 * @return: an integer representation of the key.
 */
int flexarray_get_key(flexarray f) {
    return atoi(f->key);
}
