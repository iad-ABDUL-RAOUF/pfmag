#include "data.h"

Data* createLogweights(unsigned int len);

Data* createNormalisedWeights(const Data* logweights);

double logSumWeight(const Data* logweights);