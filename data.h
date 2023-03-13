#ifndef DATA_H
#define DATA_H

// Data is a convenient structure to store and access N vectors of dimention D.

// Notice that the struct Data is declared without it's member. the goal is to 
// protect them. Users including data.h cannot mess up with Data. They can only
// interact with it through the exposed functions.
// Remarq : if you have an "incomplete type" bug it is because the user can only
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

// getVal return the reference of the first element of the i-th vector
double* getVal(Data* data, unsigned int i);
unsigned int getLen(Data* data);
unsigned int getDim(Data* data);

#endif
