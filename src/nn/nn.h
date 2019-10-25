/**
 * @file nn.h
 * @author Joe Biwer
 * @date 10-24-2019
 * @brief Neural Network library header file
 */


#ifndef _NN_H
#define _NN_H

#include "../Matrix/Matrix.h"

/**
 * @brief Feed forward algorithm for Neural Network
 * @param data Input data for network (1xn vector)
 * @return output Output data from resulting from the feed forward algorithm (1xn vector)
 */
Matrix* NN_feedforward(Matrix *m);

#endif /* _NN_H */
