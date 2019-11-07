/**
 * @file Matrix.c
 * @author Joe Biwer
 * @date 5-7-2019
 * @brief Matrix library implementation
 */


#include "Matrix.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/****************** Private Declarations ******************/
static char* get_raw_input_str(Matrix*);



#define DISPLAY_OFFSET				5



/****************** Public Functions ******************/

Matrix* Matrix_create(int rows, int columns) {
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	m->matrix = (float *)malloc(sizeof(float) * rows * columns);	
	memset(m->matrix, 0, rows*columns*sizeof(float));
	m->rows = rows;
	m->columns = columns;
	return m;
}


Matrix* Matrix_set(float data[], int row, int col) {
	Matrix *m = Matrix_create(row, col);
	m->matrix = data;
	return m;
}


void Matrix_print(Matrix *m) {
	int i, j;
	for(i = 0; i < m->rows; i++) {
		int k;
		for(k = 0; k < DISPLAY_OFFSET; k++)
			printf(" "); 
				
		for(j = 0; j < m->columns; j++) {
			printf("%6.3f ", *(m->matrix + i*m->columns + j));			// Using outer loop and row width as an offset 
		}
		printf("\n");
	}
}



void Matrix_randomize(Matrix *m) {
	int i, j;
	for(i = 0; i < m->rows; i++)
		for(j = 0; j < m->columns; j++)
			*(m->matrix + i*m->columns + j) = (rand() % MATRIX_MAX_DATA) * 0.001f; 
}


Matrix* Matrix_rawInput(char *input) {
	// Data format: [ r1_c1 r1_c2 r1_c3; r2_c1 r2_c2 r2_c3 ]
	// Decoding string, store in array
	char *token;
	int rows, columns;
	char strings[512][1024];					// String buffer for each line

	rows = 0;
	token = strtok(input, ";");
	while(token != NULL) {
		strcpy(strings[rows], token);
		rows++;
		token = strtok(NULL, ";");
	}

	if(strings[0][0] == '[')			strings[0][0] = ' ';

	// Getting amount of columns
	char temp[1024];	
	strcpy(temp, strings[0]);
	columns = 0;
	token = strtok(temp, " ");

	while(token != NULL) {
		columns++;
		token = strtok(NULL, " ");
	}

	Matrix *m = Matrix_create(rows, columns);

	// Gathering data
	float *data = malloc(sizeof(float) * rows * columns);
	
	// Processing data into array
	int i = 0;
	int j;

	for(j = 0; j < rows; j++) {
		token = strtok(strings[j], " ");
		while(token != NULL) {
			if(strcmp(token, "") != 0) {	
				if(token[0] == '[')
					token[0] = ' ';
				*(data + i) = atof(token);
			}
			i++;
			token = strtok(NULL, " ");
		}
	}

	m->matrix = data;

	return m;
}


// ---------- Element-wise Operations ----------
Matrix* Matrix_dotProduct(Matrix *m1, Matrix *m2) {
	if((m1->rows != m2->rows) || (m1->columns != m2->columns)) {
		return NULL;																// If the dimensions of the matricies do not match		
	}

	Matrix *result = Matrix_create(m1->rows, m1->columns);			// Creating new matrix to hold the result
	int i, j;
	for(i = 0; i < m1->rows; i++)
		for(j = 0; j < m1->columns; j++)
			*(result->matrix + i*result->columns + j) =
			  	*(m1->matrix + i*m1->columns + j) *
		  	 	*(m2->matrix + i*m2->columns + j);	  
	return result;
}



Matrix* Matrix_subtract(Matrix *m1, Matrix *m2) {
	if((m1->rows != m2->rows) || (m1->columns != m2->columns)) {
		return NULL;																// If the dimensions of the matricies do not match		
	}

	Matrix *result = Matrix_create(m1->rows, m1->columns);			// Creating new matrix to hold the result
	int i, j;
	for(i = 0; i < m1->rows; i++)
		for(j = 0; j < m1->columns; j++)
			*(result->matrix + i*result->columns + j) =
			  	*(m1->matrix + i*m1->columns + j) - 
		  	 	*(m2->matrix + i*m2->columns + j);	  
	return result;
}




Matrix* Matrix_add(Matrix *m1, Matrix *m2) {
	if((m1->rows != m2->rows) || (m1->columns != m2->columns)) {
		return NULL;																// If the dimensions of the matricies do not match		
	}

	Matrix *result = Matrix_create(m1->rows, m1->columns);			// Creating new matrix to hold the result
	int i, j;
	for(i = 0; i < m1->rows; i++)
		for(j = 0; j < m1->columns; j++)
			*(result->matrix + i*result->columns + j) =
			  	*(m1->matrix + i*m1->columns + j) + 
		  	 	*(m2->matrix + i*m2->columns + j);	  
	return result;
}


Matrix* Matrix_multiply(Matrix *m1, Matrix *m2) {
	if(m1->columns != m2->rows) {
		return NULL;																// If the dimensions of the matricies do not match		
	}

	Matrix *result = Matrix_create(m1->rows, m2->columns);			// Creating new matrix to hold the result
	int i, j, k;
	for(i = 0; i < m1->rows; i++)
		for(k = 0; k < m2->columns; k++) {
			float sum = 0;
			for(j = 0; j < m2->rows; j++) {
				//printf("i: %d, j: %d, k: %d\n", i, j, k);
				float num1 = *(m1->matrix + i*m1->columns + j);
				float num2 = *(m2->matrix + j*m2->columns + k);
				sum += num1 * num2;
			}
			*(result->matrix + i*result->columns + k) = sum;
		}
	return result;
}


Matrix* Matrix_transpose(Matrix *m) {	
	//char str = get_raw_intput_str(m);
	Matrix *m_t = Matrix_create(m->columns, m->rows);

	int i, j;
	for(i = 0; i < m->rows; i++)
		for(j = 0; j < m->columns; j++)
			*(m_t->matrix + j * m_t->columns + i) = *(m->matrix + i * m->columns + j); 

	return m_t;
}


Matrix* Matrix_map(float (*func)(float), Matrix *m) {

	Matrix *m_map = Matrix_create(m->rows, m->columns);
	
	int i, j;
	for(i = 0; i < m->rows; i++)
		for(j = 0; j < m->columns; j++)
			*(m_map->matrix + i*m_map->columns + j) = (*func)(*(m->matrix + i*m->columns + j));

	return m_map;
}








/****************** Private Functions ******************/

char* get_raw_input_str(Matrix *m) {
	char buffer[256];
	char str[10];

	sprintf(buffer, "%d", m->rows);
	strcat(buffer, ",");
	sprintf(str, "%d", m->columns);
	strcat(buffer, str);
	strcat(buffer, ".[");
	
	int total = m->rows * m->columns;
	int i;
	for(i = 0; i < total; i++) {
		float num = *(m->matrix + i);
		sprintf(str, "%3f", num);
		strcat(buffer, str);

		if(i < (total - 1)) {
			strcat(buffer, " ");
			if(((i + 1) % m->columns == 0) && (i != 0))
			  strcat(buffer, "; ");	
		}
	}	

	strcat(buffer, "]");
	//return buffer;
	return "test";
}



