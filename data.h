#ifndef DATA_H
#define DATA_H

// TODO ne mettre que la declaration sans le détail ici pour protéger les champs.
// declare the struct Data without it's member to protect them from modification 
// by users including data.h.

typedef struct Data{
    // dimension of each individual sensor readings
    unsigned int dim;
    // length : number of element
    unsigned int len;
    // values
    double** vals;
} Data;

Data createData(unsigned int dim, unsigned int len, double** vals);
Data destroyData(Data data);

double* getVal(Data data, unsigned int i);
unsigned int getLen(Data data);
unsigned int getDim(Data data);

// TODO depalcer
// A good practice might be to separate read and write csv from the above
// code and put it in another file. Essentially Data is just a container and it
// could be created by other means. It is not specific to csv file format.
Data readCsv(char* csvName);
void writeCsv(char* csvName, Data data);

#endif
