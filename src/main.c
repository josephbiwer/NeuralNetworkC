#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix/Matrix.h"
#include "nn/nn.h"
#include "./config.h"
#include "./fileio/fileio.h"


int main(int argc, char **argv) {

#ifdef DEBUG
	printf("-------- Neural Network Library in C --------\n");
	printf(" Note: Matrix library is fully documented, still working on document\n");
	printf(" Debugging program\n");
	printf("---------------------------------------------\n\n");
#endif

	// Loading NN data into memory
	CSVData *weights_1 = csv_read("data/weights_1.csv");
	CSVData *weights_2 = csv_read("data/weights_2.csv");
	CSVData *bias_1 = csv_read("data/bias_1.csv");
	CSVData *bias_2 = csv_read("data/bias_2.csv");

	// Testing to make sure that the values were indeed read into memory (and that the algo to load into memory works)
	Matrix **m = (Matrix **) malloc(sizeof(Matrix *) * 4);
	m[0] = Matrix_set(csvtofloat(weights_1), weights_1->rows, weights_1->cols);
	m[1] = Matrix_set(csvtofloat(bias_1), bias_1->rows, bias_1->cols);
	m[2] = Matrix_set(csvtofloat(weights_2), weights_2->rows, weights_2->cols);
	m[3] = Matrix_set(csvtofloat(bias_2), bias_2->rows, bias_2->cols);

	// Sample program
	NeuralNetwork nn = (NeuralNetwork){						\
		.arch = (Architecture){									\
			.inputs = 5,											\
			.hidden_layers = 1,									\
			.hidden_nodes = 4,									\
			.outputs = 4											\
		}																\
	};

	// Setting the layers of the neural network
	NN_set(m, 4, &nn);

#ifdef DEBUG
	printf("Neural Network layer data:\n");
	int i;
	for(i=0; i < nn.layer_count; i++) {
		printf(" nn.layers[%d]\n", i);
		Matrix_print(nn.layers[i]);
		printf("\n");
	}
#endif

	// Get input data from can bus and convert data to float variables
	float input_data[] = {195,195,195,195,195};
	printf("input data:\n   ");
	int i;
	for(i = 0; i < 5; i++) {
		printf("%6.3f ", input_data[i]);
	}
	printf("\n");

	Matrix *result = NN_feedforward(nn, input_data);

	printf("\n ***** Result *****\n");
	Matrix_print(result);

	return 0;
}
