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
    neuron *neurons;
    int num_neurons;
    double **results;
};



/* Allocates memory and initializes the values for a new neural network.
 * parameter - layers: an array of the sizes of each layer of neurons.
 * parameter - layer_size: the number of layers in the network.
 * parameter - input_size: the number of input value the network will have.
 * parameter - num_neurons: the total number of neurons in the array.
 * returns - nn: the neural network.
 */
neuralnet neuralnet_new(int *layers, int layer_size, int input_size, int num_neurons) {
    int i, j, count = 0;
    neuralnet nn = emalloc(sizeof * nn);
    nn->layers = emalloc(layer_size * sizeof layers[0]);
    nn->num_layers = layer_size;
    nn->num_neurons = num_neurons;
    nn->results = emalloc(sizeof * nn->results);
    for (i = 0; i < nn->num_layers; i++) {
        nn->results[i] = emalloc(nn->layers[i] * sizeof nn->results[0][0]);
    }
    nn->neurons = emalloc(num_neurons * sizeof nn->neurons[0]);
    for (i = 0; i < layer_size; i++) {
        for (j = 0; j < layers[i]; j++) {
            if (i == 0) {
                nn->neurons[count++] = neuron_new(i, input_size);
            } else {
                nn->neurons[count++] = neuron_new(i, layers[i - 1]);
            }
        }
    }
    return nn;
}



/* Deallocate momory used for the network.
 * parameter - nn: the network to free.
 */
void neuralnet_free(neuralnet nn) {
    int i;
    for (i = 0; i < nn->num_neurons; i++) {
        neuron_free(nn->neurons[i]);
    }
    for (i = 0; i < nn->num_layers; i++) {
        free(nn->results[i]);
    }
    free(nn->results);
    free(nn->neurons);
    free(nn->layers);
    free(nn);
}


/* Print the contents of the neural network by calling neuron print for each
 * individul neuron.
 */
void neuralnet_print(neuralnet nn) {
    int i;
    printf("Network neurons:\n");
    for (i = 0; i < nn->num_neurons; i++) {
        neuron_print(nn->neurons[i]);
    }
}


/* neuralnet_predict feeds input forward through the network using the
 * forward pass function and passes the result through the sugmoid function
 * before updating the respective position on the results matrix.
 * parameter - nn: the neuralnet.
 * parameter - inputs: tje input values.
 */
void neuralnet_predict(neuralnet nn, double *inputs) {
    int i, j, count = 0;
    for (i = 0; i < nn->num_layers; i++) {
        for (j = 0; j < nn->layers[i]; j++) {
            if (i == 0) {
                nn->results[i][j] = sigmoid(forward_pass(inputs, nn->neurons[count]));
                count++;
            } else {
                nn->results[i][j] = sigmoid(forward_pass(nn->results[i - 1], nn->neurons[count]));
                count++;
            }
        }
    }
}
