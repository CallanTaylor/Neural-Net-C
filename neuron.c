#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mylib.h"
#include "neuron.h"


/* Struct for a single Neuron.
 * layer: the depth of the neuron in the network begining at 0.
 * num_inputs: the number of values that affect the neurons output.
 * bais: a constant adding to the neurons output.
 * weights: the 'significance' of each input value.
 */
struct neuronrec {
    int layer;
    int num_inputs;
    double bais;
    double *weights;
    double result;
};



/* Allocates memory and initializes values for weights and bais as random value
 * between -1 and 1.
 * parameter - layuer: the position of the neuron in the network.
 * parameter - num_inputs: the number of input values the neuron has.
 * returns - n: the new neuron.
 */
neuron neuron_new(int layer, int num_inputs) {
    neuron n = emalloc(sizeof * n);
    int i;
    srand(time(NULL));
    n->layer = layer;
    n->result = 0.0;
    n->num_inputs = num_inputs;
    n->bais = (double)rand()/RAND_MAX*2.0-1.0;
    n->weights = emalloc(n->num_inputs * sizeof n->weights[0]);
    for (i = 0; i < num_inputs; i++) {
        n->weights[i] = (double)rand()/RAND_MAX*2.0-1.0;
    }
    return n;
}


/* Simple infomation about the neuron for testing.
 * parameter - n: the neuron that we wish to see info for.
 */
void neuron_print(neuron n) {
    int i;
    printf("Neuron at layer %d has %d inputs\n", n->layer, n->num_inputs);
    for (i = 0; i < n->num_inputs; i++) {
        printf("Input %d has weight %f \n", i, n->weights[i]);
    }
    printf("Bais: %f \n", n->bais);
}


/* Deallocated memory for neuron
 * parameter - n: the neuron to free.
 */
void neuron_free(neuron n) {
    free(n->weights);
    free(n);
}


/* Computes the output value of a given neuron for given input values.
 * parameter - inputs: the input values (either the raw data, or the results of
 * the last layers calculation).
 * parameter - n: the neuron we are findong the output for.
 * returns - result: the output value of the calculation (note that the result
 * has not been put through the sigmoid function, this is because the
 * back_propogate function needs the raw predicition value to compute the
 * partial derivitive).
 */
double forward_pass(double *inputs, neuron n) {
    int i;
    double result;
    result = n->bais;
    for (i = 0; i < n->num_inputs; i++) {
        result += inputs[i] * n->weights[i];
    }
    return result;
}
