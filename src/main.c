/**
 * @file main.c
 * @author Joe Biwer
 * @date 10-24-2019
 * @brief Entry point to the sample program that shows basic configuration of the neural network and how to use it for processing data
 */


#include "Matrix/Matrix.h"
#include "nn/nn.h"



int main(int argc, char **argv) {

	// Simulating data coming in from the CAN bus
	float input_data[] = {195, 195, 40, 195, 195};
	
	// Initialize neural network
	NeuralNetwork nn = (NeuralNetwork){						\
		.arch = (Architecture){									\
			.inputs = 5,											\
			.hidden_layers = 1,									\
			.hidden_nodes = 6,									\
			.outputs = 4											\
		}																\
	};

	// Result of the network (access array of values: result->matrix[i])
	Matrix *result = NN_feedforward(nn, input_data);



	// Printing resulting matrix to the terminal
	Matrix_print(result);

	return 0;
}
