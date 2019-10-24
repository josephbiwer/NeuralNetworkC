#include <stdio.h>
#include "Matrix/Matrix.h"


int main(int argc, char **argv) {

	// Simulating values from sensors
	int data[] = {0xC0, 0xC0, 0xC0, 0x08, 0xC0};	

	Matrix *matrix = Matrix_create(4, 5);

	Matrix_print(matrix);

	return 0;
}
