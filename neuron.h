#ifndef NEURON_H_
#define NEURON_H_


typedef struct neuronrec *neuron;


extern neuron   neuron_new(int layer, int num_inputs);
extern void     neuron_free(neuron n);
extern void     neuron_print(neuron n);
extern double   forward_pass(double *inputs, neuron n);
extern void     back_propogate(double *train, int label, neuron n);


#endif
