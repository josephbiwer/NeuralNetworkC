/**
 * @file fileio.c
 * @author Joe Biwer
 * @date 10-5-2019
 * @brief File io operation implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "fileio.h"

#define KB		1024
#define MB		KB * 1024
#define GB		MB * 1024


/***************** FILE/DIR Operations *****************/
/**
 * @brief Get file names of all .csv files inside the specified directory
 * @param dr Directory to search for the files in
 * @return files List of .csv files that were present in the directory
 */
static char**
dir_getcsv(DIR *dr) {
	struct dirent *de;
	int count = 0;
	
	// Allocating array of strings for file names
	char  **files = (char **) malloc(sizeof(char *) * 100);
	int i;
	for(i = 0; i < 100; i++)
		files[i] = (char *) malloc(sizeof(char) * 100);

	// Get files from directory
	while((de = readdir(dr)) != NULL) {

		char file_name[40];									// Making copy of file name to use (strtok modifies original string)
		strcpy(file_name, de->d_name);					// Copying file name

		char file_ext[10];									// Allocating array to hold file extension
		char *token = strtok(de->d_name, ".");			// Tokenize string

		while(token) {											// While token exists
			strcpy(file_ext, token);						// Copy token into file extension
			token = strtok(NULL, ".");						// Get next token
		}

		// The file extension is stored in file_ext at this point

		if(strcmp(file_ext, "csv") == 0) {				// File extension == csv?	
			strcpy(files[count], file_name);				//			if so, copy the file name into an array that is to be returned later
			count++;												//			increase count of csv files stored in the array
		}
			
	}				// If more files exist, keep reading them into memory

	return files;												// Return csv files
}


char** dir_get(const char *path) {

	DIR *dr = opendir(path);								// Attempt to open specified directoy

	if(dr == NULL) {											// If the program couldn't open the directory
		printf("can't open the specified directory\n");
		return NULL;											// Print error message and return null
	}

	char **files = dir_getcsv(dr);						// Get file names of all csv data in specified directory

	closedir(dr);												// Close the directory
	return files;												// Return all csv file names
}



/***************** File I/O Operations *****************/
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

	strcpy(dat->name, file);												// Copy file name into data struct

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
