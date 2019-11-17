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
	char file_path[50];														// Buffer to hold the file path

	strcpy(file_path, data_path);											// Constructing file path
	strcat(file_path, "order.txt");
	FileData *files = file_read(file_path);									// Reading in data from specified file	

	Matrix **m = (Matrix **) malloc(sizeof(Matrix *) * files->rows);		// Declaring 2D matrix of matricies

	// Reading in files from memory, converting the data to a 2D matrix, then converting the strings in the csv data structure to float vars	
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

	// Initializing neural network
	NeuralNetwork nn;

	// Setting the layers of the neural network
	NN_set(m, 4, &nn);

	// Get input data from can bus and convert data to float variables
	float input_data[] = {195,195,195,195,195};

	Matrix *result = NN_feedforward(nn, input_data);

	printf("\n ***** Result *****\n");
	Matrix_print(result);

	return 0;
}
