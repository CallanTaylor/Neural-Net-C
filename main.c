#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "neuron.h"
#include "neuralnet.h"


int main(void) {

    int *l;
    neuralnet nn;


    double *inputs = get_inputs("mnist_train.txt", 7);

    /*
    for (i = 0; i < 784; i++) {
        if (columns < 27) {
            printf("%.1f  ", inputs[i]);
            columns++;
        } else {
            printf("%.1f  \n", inputs[i]);
            columns = 0;
        }
    }
    */

    l = emalloc(2 * sizeof l[0]);
    l[0] = 10;
    l[1] = 10;
    nn = neuralnet_new(l, 2, 10);
    neuralnet_predict(nn, inputs);
    neuralnet_free(nn);
    free(inputs);
    free(l);
    

    return EXIT_SUCCESS;
}
