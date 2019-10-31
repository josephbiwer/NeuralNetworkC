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

static float
sigmoid(float x) {
	return 1 / (1 + exp(-x));
}

Matrix* NN_sigmoid_map(Matrix *m) {
	Matrix *result;								// Create new Matrix element
	result = Matrix_map(sigmoid, m);			// Map sigmoid function to the matrix elements
	return result;									// Return result
}

Matrix* NN_feedforward(NeuralNetwork nn, float data[]) {

	// ----- Building architecture of network -----
	Matrix *inputs = Matrix_set(data, 1, nn.arch.inputs);				// Defining vector and setting to input data
	Matrix *hidden = Matrix_create(1, nn.arch.hidden_nodes);			// Creating vector for input nodes
	Matrix *output = Matrix_create(1, nn.arch.outputs); 				// Creating vector for output nodes


	float weights_1[] = {\
		4.6013571, 4.17197193, -6.30956245, -4.19745118,\
		-2.58413484, -5.81447929, -6.60793435, -3.68396123,\
		0.97538679, -2.02685775,  2.52949751,  5.84371739\
	};

	float weights_2[] = {\
		-6.96765763, 7.14101949, -10.31917382, 7.86128405 \
	};

	//float weights_1[] = {\
	//	-0.7293232853137476,-2.1108090460232027,-25.178581297772112,-0.36801674821014524,\
	//	-0.07287903009066131,-2.55820960369953,-25.71439551784894,1.1231184084580337,\
	//	-0.4641366439676461,-2.1569454551827567,-25.313741274462522,1.045332789520029,\
	//	-0.2497214493659639,-2.061087243919641,-25.339871447104564,-0.42549378931308357,\
	//	-0.5489018487848367,-1.3348059924216866,-23.64128678222155,1.064103346821578\
	//};

	//float weights_2[] = {\
	//	-0.24730947968676564,-0.906186455270056,\
	//	0.3923798168371024,-0.2813871481357332,\
	//	15.146355132976614,-21.428578160356825,\
	//	31.926314856202108,-42.28649232320101\
	//};

	Matrix *syn_weights_1 = Matrix_set(weights_1, nn.arch.inputs, nn.arch.hidden_nodes);			// Creating first layer of weights
	Matrix *syn_weights_2 = Matrix_set(weights_2, nn.arch.hidden_nodes, nn.arch.outputs);			// Creating second layer of weights

	//#ifdef DEBUG
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
		printf(" ------------------------------\n\n");
	//#endif
	
	Matrix *l0 = inputs;
	Matrix *l1 = NN_sigmoid_map(Matrix_multiply(l0, syn_weights_1));
	Matrix *l2 = NN_sigmoid_map(Matrix_multiply(l1, syn_weights_2));

	return l2;	
}


