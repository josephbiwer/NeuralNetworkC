#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix/Matrix.h"
#include "nn/nn.h"
#include "./config.h"


int main(int argc, char **argv) {

#ifdef DEBUG
	printf("-------- Neural Network Library in C --------\n");
	printf(" Note: Matrix library is fully documented, still working on document\n");
	printf(" Debugging program\n");
	printf("---------------------------------------------\n\n");
#endif

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

#ifdef DEBUG
	printf("\n ***** Result *****\n");
#endif
	Matrix_print(result);

	return 0;
}
