/**
 * @file fileio.h
 * @author Joe Biwer
 * @date 10-5-2019
 * @brief Header file for file io operations
 */


#ifndef _FILEIO_H
#define _FILEIO_H

typedef struct {
	char **buffer;
	int rows;
} FileData;				/**< Buffer to read data from file that organizes the data in such a way that the data is organized by each row in the file */

typedef struct {
	int rows, cols;
	char **data;
} CSVData;

/**
 * @brief Read data from csv file and return array of strings
 * @param file File to load in data from
 * @return data Data read in from the specified file
 */
CSVData* csv_read(char *);

/**
 * @brief Read from file and return file contents
 * @param file File to read data into buffer from
 * @return data Contents from file stored in a buffer with the amount of rows read associated with the file
 */
FileData* file_read(char *);

/**
 * @brief Convert csv string to float
 * @param data CSV data to be converted
 * @return float_data Converted float data
 */
float* csvtofloat(CSVData *);


#endif /* _FILEIO_H */
