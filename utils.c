#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"


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
int *get_inputs(char *file) {
    FILE *infile = fopen(file, "r");
    flexarray *f = emalloc(784 * sizeof f[0]);
    int *inputs = emalloc(784 * sizeof inputs[0]);
    char c;
    int num_inputs = 0, i;

    for (i = 0; i < 784; i++) {
      f[i] = flexarray_new();
    }

    if (infile) {
        c = getc(infile);
        c = getc(infile);
        while (EOF != (c = getc(infile)) && num_inputs < 784) {
            if (c >= '0' && c <= '9') {
              flexarray_append(f[num_inputs], c);
            } else {
              inputs[num_inputs] = flexarray_get_key(f[num_inputs]);
              num_inputs++;
            }
        }
    }

    for (i = 0; i < 784; i++) {
      free(f[i]);
    }

    free(f);
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
