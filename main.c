#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "neuron.h"
#include "neuralnet.h"


int main(void) {

    
    int i, columns = 0;
    
    int *inputs = get_inputs("mnist_train.txt");
    

    
    for (i = 0; i < 784; i++) {
        if (columns < 27) {
            printf("%3d ", inputs[i]);
            columns++;
        } else {
            printf("%3d\n", inputs[i]);
            columns = 0;
        }
    }
    
    
    free(inputs);
 
    /*
    print_input("mnist_train.txt");
    */
    
    /* for testing if the net works 
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
    */

    return EXIT_SUCCESS;
}
