#include "data.h"

// allocate Data of size len x 1
Data* createLogweights(unsigned int len);
// allocate Data of size len x 1 and fill it with normilized weight computed from logweights
Data* createNormalisedWeights(const Data* logweights);
// return log(sum(weights)) from logweight data. Usefull to compute normalised weights
double logSumWeight(const Data* logweights);