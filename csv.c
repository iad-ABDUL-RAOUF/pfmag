#include "csv.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LINEMAXCHAR 1024
#define VALMAXCHAR 128

// simple (but limited) implementation based on :
// https://stdin.top/posts/csv-in-c/
Data* readCsv(const char* filename, const char* separator){
    FILE *file = fopen(filename,'r');
    if (file == NULL){
        printf("readCsv could not open file");
        exit(EXIT_FAILURE);
    }

    // skip the first line (assumes it is header commentary)
    char row[LINEMAXCHAR];
    fgets(row, LINEMAXCHAR, file);

    // read the rest of the file
    Data* data = readCsvFile(file, separator);
    
    fclose(file);
    return data;
}

void writeCsv(const char* filename, const Data* data, const char* header){
    // open file
    FILE* file = fopen(filename,"w");
    if (file == NULL){
        printf("writeCsv could not open file");
        exit(EXIT_FAILURE);
    }

    // add an end of line to the header and write it in the file
    char firstrow[sizeof(header)+1];
    snprintf(firstrow, sizeof(firstrow), "%s%s", header, "\n");
    fprintf(file,firstrow);

    // write data in the file
    unsigned int dim = getDim(data);
    unsigned int length = getLen(data);
    for (unsigned int i=0; i<length; ++i){
        double* values = getVal(data, i);
        char row[LINEMAXCHAR] = ""; 
        for (unsigned int d=0; d<dim; ++d){
            snprintf(row, sizeof(row), "%s%f,", row, values[d]);
        }
        if (dim > 0){
            // replace the last ',' by an end of line
            row[strlen(row)-1] = '\n';
        }
        fprintf(file,row);
    }

    fprintf(file,"\n");
    fclose(file);
}

Data* readCsvFile(FILE* file, const char* separator){

    // find what is data shape and initializes it
    char row[LINEMAXCHAR];
    Data* data;
    unsigned int dim;
    if(fgets(row, LINEMAXCHAR, file) == EOF){
        // csv file is empty
        dim = 0;
        data = createData(dim,0);
    }
    else{
        unsigned int nline = getNLine(file);
        dim = getNValues(row, separator);
        data = createData(dim,nline);
        double values[dim]; 
        parseRow(row, separator, values);
        setVal(data, 0, values);
    }
    
    // read file line by line and fills up output data
    unsigned int i = 1;
    while (fgets(row, LINEMAXCHAR, file) != EOF){
        double values[dim]; 
        unsigned int nvals = getNValues(row, separator);
        // skip empty lines and test that each line has the same number of element
        if (nvals!=dim && nvals==0){
            printf("csv file has lines of unequal length");
            exit(EXIT_FAILURE);
        }else if(nvals==dim){
            parseRow(row, separator, values);
            setVal(data, i, values);
            ++i;
        }
    }
    return data;
}

void parseRow(const char* row, const char* separator, double* values){
    // tokenizes each line (i.e. parse them taking into account the
    // separator)
    // start by coping row because strtok input is not const
    char rowcopy[sizeof(row)];
    strcpy(rowcopy,row); 
    unsigned int i = 0;
    char *token = strtok(rowcopy, separator);
    while(token != NULL){
        values[i] = atof(token);
        ++i;
        token = strtok(NULL, separator);
        
    }
}

unsigned int getNValues(const char* row, const char* separator){
    char rowcopy[sizeof(row)];
    strcpy(rowcopy,row); 
    unsigned int i = 0;
    char *token = strtok(rowcopy, separator);
    while(token != NULL){
        ++i;
        token = strtok(NULL, separator);
    }
    return i;
}

unsigned int getNLine(FILE* file){
    int initialPosition = ftell(file);
    
    // loop through the file, stoping at each end of line
    unsigned int nLine = 0;
    char row[LINEMAXCHAR];
    while (fgets(row, LINEMAXCHAR, file) != EOF){
        ++nLine;
    }
    
    // set the file stream position where it was before looping 
    fseek(file, initialPosition, SEEK_SET);
    return nLine;
}

