#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "flexarray.h"
#include "mylib.h"

#define DEFAULT_SIZE 6000


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



int *get_labels(char *file) {
    FILE *infile = fopen(file, "r");
    int label, count = 0, i = 0;
    char c;
    int *labels = emalloc(DEFAULT_SIZE * sizeof labels[0]);

    if (infile) {
        while (EOF != (c = getc(infile)) && i < DEFAULT_SIZE) {
            if (c == ',' || c == '\n') {
                count++;
                c = getc(infile);
            }
            if (count % 785 == 0) {
                label = c - '0';
                labels[i++] = label;
            }
        }
    }

    fclose(infile);

    return labels;
}


int *get_inputs(char *file) {
    FILE *infile = fopen(file, "r");
    flexarray f = flexarray_new();
    int *inputs = emalloc(784 * sizeof inputs[0]);
    char c;
    int num_inputs = 0;

    if (infile) {
        c = getc(infile);
        while (EOF != (c) && num_inputs < 784) {;
            if (c != ',' && c != '\n') {
                flexarray_append(f, c);
            }
            if (c == ',' || c == '\n') {
                inputs[num_inputs++] = flexarray_get_key(f);
                flexarray_refresh(f);
            }
            c = getc(infile);
        }
    }
    return inputs;
}


void print_input(char *file) {
    FILE *infile = fopen(file, "r");
    char c;
    int num_inputs = 0, columns = 0;

    if (infile) {
        while (EOF != (c = getc(infile)) && num_inputs < 784) {
            if (c != ',' && c != '\n') {
                if (columns < 28) {
                    printf("%c ", c);
                    columns++;
                } else {
                    printf("%c\n", c);
                    columns = 0;
                }
                num_inputs++;
                
            }
        }
    }
}
