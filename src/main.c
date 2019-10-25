#include <stdio.h>
#include "Matrix/Matrix.h"


int main(int argc, char **argv) {

	// Simulating values from sensors
	float data[] = {0xC0, 0xC0, 0xC0, 0x08, 0xC0};	
	printf("sizeof(data): %lu\n", sizeof(data)/sizeof(int));

	Matrix *matrix = Matrix_create(4, 5);
	Matrix *weights1 = Matrix_create(4, 4);

	Matrix_print(matrix);

	printf("creating vector\n");
	Matrix *vec = Matrix_set(data, 1, sizeof(data)/sizeof(int));

	Matrix_print(vec);

	return 0;
}
