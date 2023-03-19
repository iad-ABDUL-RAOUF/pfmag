#include "weight.h"
#include "math.h"

Data* createLogweights(unsigned int len){
    Data* logweights = createData(1,len);
    return logweights;
}

// Data* createWeights(const Data* logweights){
//     unsigned int len = getLen(logweights);
//     Data* weights = createData(1, len);
//     for (unsigned int i = 0; i<len; i++){
//         setScalarVal(weights, i, exp(*getVal(logweights,i)));
//     }
//     return weights;
// } // TODO remove et aussi dans .h 

Data* createNormalisedWeights(const Data* logweights){
    unsigned int len = getLen(logweights);
    double logsum = stableLogSumWeight(logweights);
    Data* weights = createData(1, len);
    for (unsigned int i = 0; i<len; i++){
        setScalarVal(weights, i, exp(*getVal(logweights,i) - logsum));
    }
    return weights;
}

// void applyLog(const Data* weights, Data* logweights){
//     unsigned int len = getLen(logweights);
//     for (unsigned int i = 0; i<len; i++){
//         setScalarVal(logweights, i, log(*getVal(weights,i)));
//     }
// } // TOD remove et dans .h aussi

double stableLogSumWeight(const Data* logweights){
    
}