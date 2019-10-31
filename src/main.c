#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix/Matrix.h"
#include "nn/nn.h"
#include "./config.h"


int main(int argc, char **argv) {

	float input_data[] = {0, 1, 1};

	// Sample program
	NeuralNetwork nn = (NeuralNetwork){\
		.arch = (Architecture){\
			.inputs = sizeof(input_data)/sizeof(float),\
			.hidden_layers = 1,\
			.hidden_nodes = 4,\
			.outputs = 1\
		}\
	};

	Matrix *result = NN_feedforward(nn, input_data);

	printf("\n ***** Result *****\n");
	Matrix_print(result);
	printf(" ******************\n\n");

	// Simulating values from sensors
	//float data[] = {0xC0, 0xC0, 0xC0, 0x08, 0xC0};	
	//int inputLength = (int)(sizeof(data) / sizeof(float));

	//NeuralNetwork nn = (NeuralNetwork){.arch = (Architecture){.inputs = inputLength, .hidden_layers = 1, .hidden_nodes = 4, .outputs = 2}};

	//Matrix *result = NN_feedforward(nn, data);




	//Matrix *test_matrix = Matrix_create(4,4);
	////test_matrix = Matrix_map(test, test_matrix);
	////Matrix_print(test_matrix);

	//printf("printing sigmoid mapped array\n");
	//test_matrix = NN_sigmoid_map(test_matrix);
	//Matrix_print(test_matrix);

	//// Random seed used for testing
	//srand(time(0));


	//// Create matrix from input data
	//Matrix *input_vec = Matrix_set(data, 1, inputLength);
	//
	//// Creating weights and randomizing
	//Matrix *weights1 = Matrix_create(inputLength, HIDDEN_NODE_COUNT);
	//Matrix_randomize(weights1);

	//// Printing results
	//printf("\nInput vector:\n");
	//Matrix_print(input_vec);
	//printf("\nRandomized weights:\n");
	//Matrix_print(weights1);
	//printf("\nOutput matrix\n");
	//Matrix_print(prod);


	//printf("\n\nTransposed matrix:\n");

	//Matrix *matrix_T = Matrix_transpose(matrix);
	//
	//Matrix_print(matrix_T);


	// Creating hidden node vector
		


	return 0;
}
