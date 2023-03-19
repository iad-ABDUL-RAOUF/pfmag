#include "data.h"

#ifndef ESTIMATES_H
#define ESTIMATES_H

typedef double (*Integrand)(const double* state, void* params);

double integrate(
    const Data* states,
    const Data* weights,
    const Integrand integrand
);

typedef void (*ComputeEstimates)(
    const Data* states,
    const Data* logweights,
    unsigned int currentIteration,
    Data* estimates
);

#endif
