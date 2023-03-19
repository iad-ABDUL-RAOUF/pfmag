#include "data.h"

#include <stdlib.h>
#include <stdio.h>

struct Data{
    // dimension of each individual sensor readings
    unsigned int dim;
    // length : number of element
    unsigned int len;
    // values
    double* vals;
};

Data* createData(unsigned int dim, unsigned int len){
    Data* data = malloc(sizeof(Data));
    if (data==NULL){
        printf("function createData failed to allocate data");
        exit(EXIT_FAILURE);
    }
    data->dim = dim;
    data->dim = len;
    data->vals = malloc(dim*len*sizeof(double));
    if (data->vals==NULL){
        printf("function createData failed to allocate data->vals");
        exit(EXIT_FAILURE);
    }
    return data;
}

void destroyData(Data* data){
    free(data->vals);
    free(data);
}

double* getVal(Data* data, unsigned int i){
    return &data->vals[i*data->dim];
}

unsigned int getLen(Data* data){
    return data->len;
}

unsigned int getDim(Data* data){
    return data->dim;
}

void setVal(Data* data, unsigned int i, double* val){
    double* dataVal = getVal(data,i);
    unsigned int dim = getDim(data);
    for (unsigned int d = 0; d<dim; ++d){
        dataVal[d] = val[d];
    }
}

void setConstantVal(Data* data, unsigned int i, double val){
    double* dataVal = getVal(data,i);
    unsigned int dim = getDim(data);
    for (unsigned int d = 0; d<dim; ++d){
        dataVal[d] = val;
    }
}
