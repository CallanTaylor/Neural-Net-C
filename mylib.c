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


#define DEFAULT_SIZE 6000


/* A function for returning the label of a single instance of the mnist training
 * data.
 * @param: file - the name of the file which contains the labels and the
 * respective input values.
 * @return: label - the value for that particular example.
 */
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


/* A function returning an array of integer values between 0 and 255
 * representing the greyscale values of each pixel in a 28 x 28 image of a
 * handdrawn digit. get_inputs uses a flexarray ADT to concatonate each value
 * and add it to a array.
 * @param: file - the filename wich contains the labels and respective input
 * values.
 * @return: inputs - the new array containg 784 in integers representing each
 * pixel.
 */
double *get_inputs(char *file, int position) {
    FILE *infile = fopen(file, "r");
    flexarray f;
    double *inputs = emalloc(784 * sizeof inputs[0]);
    char c;
    int num_inputs = 0, i;
    f = flexarray_new();

    if (infile) {
        i = 0;
        while (i < position * 785) {
            c = getc(infile);
            if (c == ',' || c == '\n') {
                i++;
            }
        }
        c = getc(infile);
        c = getc(infile);
        while (EOF != (c = getc(infile)) && num_inputs < 784) {
            if (c >= '0' && c <= '9') {
                flexarray_append(f, c);
            } else {
                inputs[num_inputs] = (double)flexarray_get_key(f)/ 255;
                flexarray_free(f);
                f = flexarray_new();
                num_inputs++;
            }
        }
    }
    if (f != NULL) {
        flexarray_free(f);
    }

    fclose(infile);
    return inputs;
}



void print_inputs(char *file) {
    FILE *infile = fopen(file, "r");
    char c;
    int num_inputs = 0, columns = 0;;

    if (infile) {
        c = getc(infile);
        c = getc(infile);
        while (EOF != (c = getc(infile)) && num_inputs < 784) {
            if (c >= '0' && c <= '9') {
                fprintf(stderr, "%c", c);
            } else {
                if (columns < 27) {
                    num_inputs++;
                    columns++;
                    fprintf(stderr, "%c", ',');
                } else {
                    num_inputs++;
                    columns = 0;
                    fprintf(stderr, "\n");
                }
            }
        }
    }
    fclose(infile);
}
