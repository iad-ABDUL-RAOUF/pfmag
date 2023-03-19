#include "data.h"
#include <stdio.h>

#ifndef CSV_H
#define CSV_H

// Read csv file. Assumes the first row is a commentary
// and ignore it.
Data* readCsv(const char* filename, const char* separator);

void writeCsv(const char* filename, const Data* data, const char* header);

// implementation details

Data* readCsvFile(FILE* file, const char* separator);

// return the number of line of a file
unsigned int getNLine(FILE* file);
// read a csv-like line and return the number of values of this line
unsigned int getNValues(const char* row, const char* separator);
// read a csv-like line and fill in values with it.
// assumes values is an array of the right size
void parseRow(const char* row, const char* separator, double* values);

#endif