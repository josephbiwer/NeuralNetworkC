/**
 * @file: nn.c
 * @author Joe Biwer
 * @date 10-24-2019
 * @brief Neural Network implementation file
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "nn.h"
#include "../Matrix/Matrix.h"



/************* Private functions *************/
/**
 * @brief Maps the value to the output of the sigmoid function at that point
 * @param x Value that is to be evalutated in the Sigmoid function
 * @return value Output of the sigmoid value evaluated at point x
 */
static float
sigmoid(float x) {
	return 1 / (1 + exp(-x));
}

/**
 * @brief Map every point in the Matrix through the sigmoid function
 * @param m Matrix to perform the operation on
 * @return result	A Matrix with every value evaluated at its corresponding point in the sigmoid function
 */
static Matrix*
NN_sigmoid_map(Matrix *m) {
	Matrix *result;								// Create new Matrix element
	result = Matrix_map(sigmoid, m);			// Map sigmoid function to the matrix elements
	return result;									// Return result
}

/**
 * @brief Remap the layers array (weights and biases) to a new layers array that contains the nodes values (inputs, hidden nodes, outputs)
 * @param m Array of Matrix points, passed by reference. [**m -> Array of Matrix pointers, *(x) -> passed by ref]
 * @param size Size of the original layers array
 * @retun new_size The size of the new_layers array
 */
static int 
NN_remap_layers(Matrix *(**m), int size) {

	// loop through the matricies to obtain each individual layer
	// The layer array architecture is as such: weights, bias, weights, bias, ....
	// 	Therefore, the matricies array should be of an even number length

	int new_size = ((size / 2) * 3) + 1;	// Determining new size of the layers array

	Matrix **new_layers = (Matrix **) malloc(sizeof(Matrix *) * new_size);			// Allocating memory for new layers array

	int i;
	for(i = 0; i < size; i+=2) {				// Create each layer of the network

		int index = (i * 2) - 1;				// Starting index for the layer in the new_layers array
														// Note: Each layer has 4 components (input, weights, bias, outputs)

		if(index == -1) {							// Input layer, creating empty matrix
			index = 0;								// 0-based indexing, need to remap the index of the layers array to 0
			new_layers[0] = Matrix_create(1, (*m)[0]->rows);				// Declaring inputs
		}	

		new_layers[index + 1] = (*m)[i];			// Weights matrix
		new_layers[index + 2] = (*m)[i + 1];	// Bias matrix
		new_layers[index + 3] = Matrix_create(1, (*m)[i+1]->columns);		// Hidden layer

	}

	*m = new_layers;								// Resetting the 2-D array that was passed by reference
	return new_size;								// Returning new size of the array

}
/*********************************************/




/************* Public functions *************/
void NN_set(Matrix **m, int size, NeuralNetwork *nn) {

	int new_size = NN_remap_layers(&m, size);		// Remap the layers array to include layers of nodes as well

	// Declaring NN values
	nn->layers = m;								// Setting nn layer data
	nn->layer_count = new_size;				// Setting layer count for future operations

}


Matrix* NN_feedforward(NeuralNetwork nn, float data[]) {

	// Declaring inputs of network
	nn.layers[0] = Matrix_set(data, 1, nn.arch.inputs);	

	// Feed forward algorithm
	int i;
	for(i = -1; i < nn.layer_count; i+=4) {
		int index = (i == -1)? 0: i;			// Remapping index 0, otherwise [index = i]
		Matrix *data = Matrix_multiply(nn.layers[index], nn.layers[index+1]);
		data = Matrix_add(data, nn.layers[index+2]);
		nn.layers[index+3] = NN_sigmoid_map(data);
	}

	return nn.layers[nn.layer_count - 1];	// Return output layer
}
