#include <stdio.h>
#include "Matrix/Matrix.h"


int main(int argc, char **argv) {

	// Simulating values from sensors
	int data[] = {0xC0, 0xC0, 0xC0, 0x08, 0xC0};	

	Matrix *matrix = Matrix_create(3, 2);
	Matrix_randomize(matrix);

	Matrix_print(matrix);


	printf("\n\nTransposed matrix:\n");

	Matrix *matrix_T = Matrix_transpose(matrix);
	
	Matrix_print(matrix_T);


	// Creating hidden node vector
		


	return 0;
}
