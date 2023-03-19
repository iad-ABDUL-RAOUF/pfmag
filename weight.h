#include "data.h"

Data* createLogweights(unsigned int len);

// Data* createWeights(const Data* logweights);

Data* createNormalisedWeights(const Data* logweights);

// void applyLog(const Data* weights, Data* logweights);

double stableLogSumWeight(const Data* logweights);