/**
 * @file nn.h
 * @author Joe Biwer
 * @date 10-24-2019
 * @brief Neural Network library header file
 */


#ifndef _NN_H
#define _NN_H

#include "../Matrix/Matrix.h"

typedef struct {
	int inputs;
	int hidden_layers;
	int hidden_nodes;
	int outputs;
} Architecture; /**< Architecture of the neural network used for initialization */

typedef struct {
	Architecture arch;
	Matrix **layers;
	int layer_count;
} NeuralNetwork; /**< Neuralnetwork struct for initializing the network. The struct consists of a struct that defines the architecture of the network as well as holds the data of each portion of the network. You must intialize the network architecture before performing and neural network operations */

/**
 * @brief Feed forward algorithm for Neural Network
 * @param data Input data for network (1xn vector)
 * @return output Output data from resulting from the feed forward algorithm (1xn vector)
 */
Matrix* NN_feedforward(NeuralNetwork, float[]);

/**
 * @brief Declare layers of the network
 * @param m	Array of matricies (Matrix struct) in the desired order (example: inputs, weights_1, bias_1, output)
 * @param size 
 * @param nn Neural Network to assign the layers to
 * @return none
 */
void NN_set(Matrix **, int size, NeuralNetwork *);

/**
 * @brief Map the sigmoid function to the specified matrix
 * @param m Matrix to apply the sigmoid function to
 * @return result Resulting matrix from sigmoid function
 */
//Matrix* NN_sigmoid_map(Matrix *);

#endif /* _NN_H */
