#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

#define DEFAULT_SIZE 6000


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
