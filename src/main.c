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
	Matrix *w_1 = Matrix_set(csvtofloat(weights_1), weights_1->rows, weights_1->cols);
	printf("weights_1 matrix:\n");
	Matrix_print(w_1);
	printf("\n");

	// Sample program
	NeuralNetwork nn = (NeuralNetwork){						\
		.arch = (Architecture){									\
			.inputs = 5,											\
			.hidden_layers = 1,									\
			.hidden_nodes = 4,									\
			.outputs = 4											\
		}																\
	};

	// Get input data from can bus and convert data to float variables
	float input_data[] = {195,195,10,195,195};

	Matrix *result = NN_feedforward(nn, input_data);

#ifdef DEBUG
	printf("\n ***** Result *****\n");
#endif
	Matrix_print(result);

	return 0;
}
