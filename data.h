#ifndef DATA_H
#define DATA_H

// Data is a convenient structure to store and access N vectors of dimention D.

// Notice that the struct Data is declared without it's member. The goal is to
// encapsulate them. Users including data.h cannot directly access to Data members.
// They can only interact with it through the exposed functions. It allows you to
// change the internal representation and implementation of Data and related fonctions.
// As long as the provided function interface holds, users should not be impacted
// by the modifications.
// Note : if you have an "incomplete type" bug it is because the user can only
// handle Data pointers and not Data itself
// Data data = ...; // is not allowed "incomplete type"
// Data* data = ...; // is allowed
// This design pattern is called a FIRST-CLASS ADT pattern.
// http://adampetersen.se/Patterns%20in%20C%201.pdf

typedef struct Data Data;

// "dim" is the dimention of each vectors
// "len" is the number of vector to store
Data* createData(unsigned int dim, unsigned int len);
void destroyData(Data* data);

// getters

// getVal return the adress of the first element of the i-th vector
double* getVal(const Data* data, unsigned int i);
// getVals return the adress of the complete array
double* getVals(const Data* data, unsigned int i);
unsigned int getLen(const Data* data);
unsigned int getDim(const Data* data);

// setters

// copy the first "dim" double from "val" into the i-th vector of data
void setVal(Data* data, unsigned int i, const double* val);
// set all component of the i-th vector of data to val 
void setScalarVal(Data* data, unsigned int i, double val);

#endif
