#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "neuron.h"
#include "neuralnet.h"



/* Struct for a neural network functions as a container for neurons so we can
 * have functions that act on the entire network.
 * layers: an array of the sizes of each layer.
 * num_neurons: the number of layers.
 * neurons: all of the neurons in the network.
 * num_neurons: the size of the whole network.
 * results: a two dimensional array of doubles representing the results of thier
 * computations.
 */
struct neuralnetrec {
    int *layers;
    int num_layers;
    neuron **neurons;
};



/* Allocates memory and initializes the values for a new neural network.
 * parameter - layers: an array of the sizes of each layer of neurons.
 * parameter - layer_size: the number of layers in the network.
 * parameter - input_size: the number of input value the network will have.
 * parameter - num_neurons: the total number of neurons in the array.
 * returns - nn: the neural network.
 */
neuralnet neuralnet_new(int *layers, int num_layers, int num_inputs) {
    int i, j, s = 0;
    neuralnet nn = emalloc(sizeof * (nn));
    nn->layers = emalloc(num_inputs * sizeof layers[0]);
    for (i = 0; i < num_layers; i++) {
        for (j = 0; j < layers[i]; j++) {
            s++;
        }
    }
    nn->neurons = emalloc(s * sizeof nn->neurons[0][0]);
    for (i = 0; i < num_layers; i++) {
        nn->layers[i] = layers[i];
    }
    nn->num_layers = num_layers;
    for (i = 0; i < num_layers; i++) {
        nn->neurons[i] = emalloc(nn->layers[i] * sizeof nn->neurons[0][0]);
    }
    for (i = 0; i < num_layers; i++) {
        for (j = 0; j < layers[i]; j++) {
            if (i == 0) {
                nn->neurons[i][j] = neuron_new(i, num_inputs);
            } else {
                nn->neurons[i][j] = neuron_new(i, layers[i - 1]);
            }
        }
    }
    return nn;
}



/* Deallocate momory used for the network.
 * parameter - nn: the network to free.
 */
void neuralnet_free(neuralnet nn) {
    int i, j;
    for (i = 0; i < nn->num_layers; i++) {
        for (j = 0; j < nn->layers[i]; j++) {
            neuron_free(nn->neurons[i][j]);
        }
        free(nn->neurons[i]);
    }
    free(nn->neurons);
    free(nn->layers);
    free(nn);
}


void neuralnet_predict(neuralnet nn, double *inputs) {
    double *prev_layer_results;
    int i, j, k;
    for (i = 0; i < nn->num_layers; i++) {
        for (j = 0; j < nn->layers[i]; j++) {
            if (i == 0) {
                forward_pass(inputs, nn->neurons[i][j]);
            } else {
                prev_layer_results =
                    emalloc(nn->layers[i - 1] * sizeof prev_layer_results[0]);
                for (k = 0; k < nn->layers[i - 1]; k++) {
                    prev_layer_results[k] = get_result(nn->neurons[i - 1][k]);
                }
                forward_pass(prev_layer_results, nn->neurons[i][j]);
                free(prev_layer_results);
            }
        }
    }
}
