#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Matrix/Matrix.h"
#include "nn/nn.h"
#include "./config.h"
#include "./fileio/fileio.h"


int main(int argc, char **argv) {

	const char* data_path = "data/";



#ifdef DEBUG
	printf("-------- Neural Network Library in C --------\n");
	printf(" Note: Matrix library is fully documented, still working on document\n");
	printf(" Debugging program\n");
	printf("---------------------------------------------\n\n");
#endif

	char file_path[50];														// Buffer to hold the file path

	strcpy(file_path, data_path);											// Constructing file path
	strcat(file_path, "order.txt");
	FileData *files = file_read(file_path);							// Reading in data from specified file

	
#ifdef DEBUG
	int r;
	for(r = 0; r < files->rows; r++) {
		int size = (int) sizeof(files->buffer[r]);
		//files->buffer[r][size - 2] = '\0';
		printf(" - %s\n", files->buffer[r]);
	}
#endif
	

	Matrix **m = (Matrix **) malloc(sizeof(Matrix *) * files->rows);		// Declaring number of matricies

	int files_itt;
	for(files_itt = 0; files_itt < files->rows; files_itt++) {
		strcpy(file_path, data_path);													// Constructing file path
		strcat(file_path, files->buffer[files_itt]);								// Getting file name from FileData struct that was declared earlier
		
		int size = (int) sizeof(file_path);											// Removing white space from file path name
		int k;
		for(k = 0; k < size; k++)
			if(file_path[k] == ' ' || file_path[k] == '\n')
				file_path[k] = '\0';

		CSVData *csv = csv_read(file_path);											// Loading data into matrix (char *)
		m[files_itt] = Matrix_set(csvtofloat(csv), csv->rows, csv->cols);	// Converting strings to floats and storing the Matrix in the matrix array
	}

#ifdef DEBUG
	int j;																					// Printing matrix data to the console
	for(j = 0; j < files_itt; j++) {
		printf(" m[%d]:\n", j);
		Matrix_print(m[j]);
		printf("\n");
	}
#endif

	// Initializing neural network
	NeuralNetwork nn;

	// Setting the layers of the neural network
	NN_set(m, 4, &nn);

	printf("\n - inputs: %d\n", nn.arch.inputs);
	printf("\n - hidden_layers: %d\n", nn.arch.hidden);
	printf("\n - outputs: %d\n", nn.arch.outputs);

	int i;
#ifdef DEBUG
	printf("Neural Network layer data:\n");
	for(i=0; i < nn.layer_count; i++) {
		printf(" nn.layers[%d]\n", i);
		Matrix_print(nn.layers[i]);
		printf("\n");
	}
#endif

	// Get input data from can bus and convert data to float variables
	float input_data[] = {195,195,195,195,195};
	printf("input data:\n   ");
	for(i = 0; i < 5; i++) {
		printf("%6.3f ", input_data[i]);
	}
	printf("\n");

	Matrix *result = NN_feedforward(nn, input_data);

	printf("\n ***** Result *****\n");
	Matrix_print(result);

	return 0;
}
