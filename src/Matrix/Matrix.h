/**
 * @file Matrix.h
 * @author Joe Biwer
 * @date 5-7-2019
 * @brief Matrix library header file
 */


#ifndef _MATRIX_H
#define _MATRIX_H

// ----- Global Declorations -----
#define MATRIX_MAX_DATA					1000
#define MATRIX_MAX_ROWS					1000

typedef struct {
	float *matrix;
	int rows, columns;
} Matrix;	/**< Holds the data of the matrix and the row/column count */

/**
 * @brief Creates a new matrix and returns it to the user
 * @return Newly created Matrix
 */
Matrix* Matrix_create(int, int);

/**
 * @brief Creates a vector (1-n matrix) and returns it to the user
 * @brief data Input data 
 * @brief row Amount of rows
 * @brief col Amount of columns
 * @return Newly created Matrix
 */
Matrix* Matrix_set(float [], int, int);

/**
 * @brief Print the matrix to the terminal
 * @param m Pointer to the matrix that is to be printed
 * @return None
 */
void Matrix_print(Matrix *);

/**
 * @brief Randomizing the matrix data
 * @param m Point to matrix that will then hold the new randomized data at the end
 * @return None
 */
void Matrix_randomize(Matrix *);

/**
 * @brief CLI tool to create a matrix
 * @return Newly created matrix (pointer) if created successfully, otherwise null if an error occured
 */ 
Matrix*  Matrix_rawInput(char *);



// ---------- Element-wise Operations -----------

/**
 * @brief Map the specified function to the elements of the specified matrix
 * @param func Function to run each element of the matrix through
 * @param m 	Matrix to perform the function operation on
 * @return res	Resulting matrix
 */
Matrix* Matrix_map(float (*f)(float), Matrix *);


/**
 * @brief Perform the transpose operation on the specified matrix, then return the result to the user
 * @param m Original matrix
 * @return Transposed matrix.
 */
Matrix* Matrix_transpose(Matrix *);

/**
 * @brief Perform the dot product (element-wise) on two matricies and return a new matrix to the user
 * @param m1 Matrix one
 * @param m2 Matrix two
 * @return Newly created matrix which is the dot product of the two matricies passed to the function, null will be returned if invalid matricies were passed to the function
 */
Matrix* Matrix_dotProduct(Matrix *, Matrix *);

/**
 * @brief Perform element-wise subtraction on the two matricies and return a new matrix to the user
 * @param m1 Matrix one
 * @param m2 Matrix two
 * @return Newly created matrix which is the sum of the two matricies (element-wise) passed to the function, null will be returned if invalid matricies were passed to the function
 */
Matrix* Matrix_subtract(Matrix *, Matrix *);

/**
 * @brief Perform element-wise addition on the two matricies and return a new matrix to the user
 * @param m1 Matrix one
 * @param m2 Matrix two
 * @return Newly created matrix which is the sum of the two matricies (element-wise) passed to the function, null will be returned if invalid matricies were passed to the function
 */
Matrix* Matrix_add(Matrix *, Matrix *);

/**
 * @brief Multiply the two matricies together [m1 x m2]
 * @param m1 Matrix one
 * @param m2 Matrix two
 * @return Newly create matrix that is the product of the two specified matricies
 */
Matrix* Matrix_multiply(Matrix *, Matrix *);

#endif /* _MATRIX_H */
