/**
 * @file fileio.c
 * @author Joe Biwer
 * @date 10-5-2019
 * @brief File io operation implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"

#define KB		1024
#define MB		KB * 1024
#define GB		MB * 1024


CSVData* csv_read(char *file) {

	// Reading data into the buffer
	FileData f_data;
	f_data = *(file_read(file));

	// CSV data structure to hold the data form the file
	CSVData *csv = (CSVData *)malloc(sizeof(CSVData));
	
	// Create array for processing data
	char **strs = (char **)malloc(sizeof(char *) * KB);			// 1 KB of data stored in csv struct 
	int k;
  	for(k = 0; k < KB; k++)
		strs[k] = (char *) malloc(sizeof(char) * 64);				// Each string is 63 chars long (+1 for terminating char)	

	csv->rows = 0;

	int i;
	int count;
	for(i = 0; i < f_data.rows; i++) {									// Each row

		// Tokenize row
		char *token = strtok(f_data.buffer[i], ",");
		if(token) {																// If token is not null
			count = 0;															// Reset count
			while(token) {														// while the token is not null
				strcpy(strs[csv->rows * csv->cols + count],token); // 	Copy the string into the buffer
				token = strtok(NULL, ",\n");								// 	get next token
				count++;
			}
		}

		csv->cols = count;
		csv->rows++;

	}	
	
	csv->data = strs;															// Copy data string into data structure and return the struct

	return csv;
}




FileData* file_read(char *file) {

	FileData *dat = (FileData *)malloc(sizeof(FileData));

#ifdef DEBUG
	printf("Opening file %s for read operation\n", file);
#endif

	FILE *fp = fopen(file, "r");											// Open file for read operation

	// Allocating buffer
	int count = KB;
	char **strs = (char **)malloc(sizeof(char *) * count);
	int k;
  	for(k = 0; k < count; k++)
		strs[k] = (char *) malloc(sizeof(char) * KB);				// Each string is 1 KB long	
	
#ifdef DBEUG
	printf("Loading data into buffer\n");
#endif

	int i = 0;
	while(fgets(strs[i], 2 * MB, fp)) {									// Read data in from file	
		i++;
	}
	
	dat->rows = i;																// Number of rows in the file
	dat->buffer = strs;

#ifdef DEBUG
	printf("data read from file into buffer of size: %d bytes\n", KB * KB);
	printf("buffer contents:\n\n");
	int j;
	for(j = 0; j < i; j++) {
		printf(" - %d: %s\n", j, strs[j]);
	}
#endif

	return dat;
}



/* ----------- Data Conversion ----------- */
float* csvtofloat(CSVData *csv) {
	float *arr = (float *)malloc(sizeof(float) * csv->rows * csv->cols);

	// Convert strings to float	
	int size = sizeof(arr) / sizeof(float);
	int i, j;
	for(i = 0; i < csv->rows; i++)
		for(j = 0; j < csv->cols; j++) {
			int index = i * csv->cols + j;
			arr[index] = atof(csv->data[index]);	
		}

	return arr;
}
