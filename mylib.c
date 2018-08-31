#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "flexarray.h"
#include "mylib.h"




void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}



void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory realloction failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}



double sigmoid(double x) {
    return  (1 / (1 + exp(-x)));
}
