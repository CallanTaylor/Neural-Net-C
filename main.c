#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mylib.h"
#include "neuron.h"
#include "neuralnet.h"


int main(void) {

    int *l = emalloc(3 * sizeof l[0]);
    double *inputs = emalloc(3 * sizeof inputs[0]);
    int i;
    neuralnet nn;
    for (i = 0; i < 3; i++) {
        inputs[i] = 0.6;
        l[i] = 3;
    }
    nn = neuralnet_new(l, 3, 3, 9);
    neuralnet_print(nn);
    neuralnet_predict(nn, inputs);
    neuralnet_free(nn);
    free(inputs);
    free(l);

    return EXIT_SUCCESS;
}
