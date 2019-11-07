/**
 * @file: nn.c
 * @author Joe Biwer
 * @date 10-24-2019
 * @brief Neural Network implementation file
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "nn.h"
#include "../Matrix/Matrix.h"



/************* Private functions *************/
static float
sigmoid(float x) {
	return 1 / (1 + exp(-x));
}

static Matrix*
NN_sigmoid_map(Matrix *m) {
	Matrix *result;								// Create new Matrix element
	result = Matrix_map(sigmoid, m);			// Map sigmoid function to the matrix elements
	return result;									// Return result
}
/*********************************************/




/************* Public functions *************/
void NN_set(Matrix **m, int size, NeuralNetwork *nn) {
	// Set NN	
	printf("size of matrix array: %d\n", size);

	/*
	nn->layers = (Layer *) malloc(sizeof(Layer *) * size);

	// Input matrix
	nn->layers[0] = (Layer *) {							\
		.index = 0,												\
		.data = Matrix_create(1, nn->arch.inputs)		\
	};

	
	// hidden layers
	int i;
	for(i = 0; i < size; i++) {
		int layers_index = i + 1;

	 	bool is_node = ((i % 2) == 0) && \						// Does the current index represent weights
			(i != 0);													// does the current node 
	}
	*/
}


Matrix* NN_feedforward(NeuralNetwork nn, float data[]) {

	// ----- Building architecture of network -----
	Matrix *inputs = Matrix_set(data, 1, nn.arch.inputs);				// Defining vector and setting to input data
	Matrix *hidden = Matrix_create(1, nn.arch.hidden_nodes);			// Creating vector for input nodes
	Matrix *output = Matrix_create(1, nn.arch.outputs); 				// Creating vector for output nodes


	float weights_1[] = {\
		-0.0402366251058734,-19.723239373684905,-0.2521069693505191,27.712463088969297,1.533517241047413,7.245798014717482,		\
		0.9351049571746403,-2.917438722459689,0.3438940160299956,6.604449439025749,0.2888666559760687,5.270042831998815,		\
		0.1764140403770721,-3.1767267061747004,-0.19696795010672327,5.445502104706753,-0.10208692624358967,4.832006134569949,	\
		0.270880844814714,-24.879469744660703,-0.2227816110816849,32.9049506548918,-0.8096849206577215,7.847453253317716,		\
		-0.04177638935594056,-24.004854654435423,-0.1271008806472212,18.636999659411394,-0.0032521198721247035,6.564237729959086\
	};

	float weights_2[] = {\
		-160.66912019035203,-37.978565273206804,-210.2022376131703,195.53151812195733,		\
		-39.372865159066855,-13.244485606884783,-35.65014912816313,36.06360530203364,		\
		-0.10037275903760033,-0.12452399767430569,0.8932761673735331,0.997716696817285,		\
		-110.7949238373287,-20.836857490213916,-158.60623407842226,149.6761687539836,		\
		-35.258319995792085,-6.969647645826791,-59.82659194119143,59.061403191986656,		\
		-136.23236168764547,-24.838078974294415,-191.2173596346913,171.68801630249348		\
	};
	
	float b_1[] = {-6.851394356106138e-08,-0.12913182620104205,2.9989037404481565e-08,0.17308301407264268,0.0032406964827805785,0.044008186011712185};	

	float b_2[] = {-161.1492147367179,-37.30113830391351,-209.94387887243315,196.45274896143476};

	Matrix *syn_weights_1 = Matrix_set(weights_1, nn.arch.inputs, nn.arch.hidden_nodes);			// Creating first layer of weights
	Matrix *syn_weights_2 = Matrix_set(weights_2, nn.arch.hidden_nodes, nn.arch.outputs);			// Creating second layer of weights
	Matrix *bias_1 = Matrix_set(b_1, 1, nn.arch.hidden_nodes);											// Creating bias for first layer of hidden nodes
   Matrix *bias_2 = Matrix_set(b_2, 1, nn.arch.outputs);													// Creating bias for output nodes	

#ifdef DEBUG
	printf(" ----- Definied Matricies -----\n");						// If debugging, print data to the console
	printf("input:\n");
	Matrix_print(inputs);
	printf("\nhidden:\n");
	Matrix_print(hidden);
	printf("output:\n");
	Matrix_print(output);
	printf("\n\nsyn_weights_1:\n");
	Matrix_print(syn_weights_1);
	printf("\nsyn_weights_2:\n");
	Matrix_print(syn_weights_2);
	printf("\n\nbias_1:\n");
	Matrix_print(bias_1);
	printf("\nbias_2:\n");
	Matrix_print(bias_2);
	printf(" ------------------------------\n\n");

	printf("\n Training the network\n\n");
#endif
	
	// ----- Feed Forward Algorithm -----
	Matrix *l0 = inputs;												// layer 0 - inputs
	Matrix *l1 = Matrix_multiply(l0, syn_weights_1);		// layer 1 - hidden layer (multiplying inputs by first layer of weights)

#ifdef DEBUG
	printf("l1 - before adding bias\n");
	Matrix_print(l1);
#endif

	l1 = Matrix_add(l1, bias_1);									// 			adding bias to layer 1

#ifdef DEBUG
	printf("l1 - before sigmoid: \n");
	Matrix_print(l1);
#endif

	l1 = NN_sigmoid_map(l1);										// 			activation function

	Matrix *l2 = Matrix_multiply(l1, syn_weights_2);		// layer 2 - output layer (multiplying hidden layer by second layer of weights)

#ifdef DEBUG
	printf("l2 - before adding bias\n");
	Matrix_print(l2);
#endif

	l2 = Matrix_add(l2, bias_2);									// 			adding bias to layer 2

#ifdef DEBUG
	printf("l2 - before sigmoid map\n");
	Matrix_print(l2);
#endif

	l2 = NN_sigmoid_map(l2);										//				activation function

	return l2;															// Return the output of the network
}


