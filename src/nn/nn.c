/**
 * @file: nn.c
 * @author Joe Biwer
 * @date 10-24-2019
 * @brief Neural Network implementation file
 */

#include <stdlib.h>
#include <stdio.h>
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
void NN_set(Matrix *m, NeuralNetwork *nn) {
	// Set NN	
}


Matrix* NN_feedforward(NeuralNetwork nn, float data[]) {

	// ----- Building architecture of network -----
	Matrix *inputs = Matrix_set(data, 1, nn.arch.inputs);				// Defining vector and setting to input data
	Matrix *hidden = Matrix_create(1, nn.arch.hidden_nodes);			// Creating vector for input nodes
	Matrix *output = Matrix_create(1, nn.arch.outputs); 				// Creating vector for output nodes


	float weights_1[] = {\
		0.43539230051843947,-0.02065032825041091,0.019108774130658146,-0.18793425230191763,	\
		0.5730059800179077,-0.3985145796820122,0.45247556261757094,-0.14951021311829882,		\
		0.0867230415726905,-0.951140545578671,-0.34949493270378973,-0.5640115159285255,		\
		0.8443632238447829,0.30048712084207874,0.48626392300583143,-0.6085350062085038,		\
		-0.5295328147011433,-0.9232621663022922,0.5697627157639107,-0.41763286028598445		\
	};

	float weights_2[] = {\
		165.34432400804772,-184.4962265107306,-235.68403926131995,-217.46373814544663,		\
		0.903049491787723,-0.09600119869105694,-0.12902490689994806,0.6458222230959201,		\
		166.4229893725542,-183.3935384234813,-236.73138036584993,-216.7631329707076,			\
		-0.28657341286209603,0.4438008781030547,0.15319508736841803,0.1728806681154469		\
	};
	
	float b_1[] = {0.0,1.9970720598181246e-80,0.0,-1.0699438457691551e-76};	

	float b_2[] = {165.82511434556375,-183.9384511051835,-236.66256225438315,-217.70618586720568};

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


