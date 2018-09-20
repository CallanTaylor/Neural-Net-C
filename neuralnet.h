#ifndef NEURALNET_H_
#define NEURALNET_H_


typedef struct neuralnetrec *neuralnet;


extern neuralnet   neuralnet_new(int *layers, int layer_size, int input_size);
extern void        neuralnet_train(double *inputs, double label);
extern void        neuralnet_free(neuralnet nn);
extern void        neuralnet_predict(neuralnet nn, double *input);
extern void        neuralnet_print(neuralnet nn);


#endif
