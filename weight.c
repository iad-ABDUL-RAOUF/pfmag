#include "weight.h"
#include <math.h>

Data* createLogweights(unsigned int len){
    Data* logweights = createData(1,len);
    return logweights;
} 

Data* createNormalisedWeights(const Data* logweights){
    unsigned int len = getLen(logweights);
    double logsum = logSumWeight(logweights);
    Data* weights = createData(1, len);
    for (unsigned int i = 0; i<len; i++){
        setScalarVal(weights, i, exp(*getVal(logweights,i) - logsum));
    }
    return weights;
}

double logSumWeight(const Data* logweights){
    // this way of computing the normalisation constant is supposedly robust
    // to numerical errors (I did not check it myself)

    // find maximum of logweight
    unsigned int len = getLen(logweights);
    double logMaxWeight = *getVal(logweights,0);
    for (unsigned int i = 1; i<len; i++){
        logMaxWeight = fmax(logMaxWeight, *getVal(logweights,i));
    }
    
    // compute normalisation constant
    double sum = 0;
    for (unsigned int i = 0; i<len; i++){
        sum += exp(*getVal(logweights,i) - logMaxWeight);
    }
    return (logMaxWeight + log(sum));
}