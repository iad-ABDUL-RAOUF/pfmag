#include "data.h"
#include "weight.h"
#include "stateXYPsi.h"

#ifndef ESTIMATESXYPSI_H
#define ESTIMATESXYPSI_H

// contain elements :
// mX, vX, mY, vY, mCosPsi, vCosPsi, mSinPsi, vSinPsi;
// with "m" denoting the mean and v denoting the variance
typedef Data EstimatesXYPsi;

Data* createEstimatesXYPsi(unsigned int len);

void computeEstimatesXYPsi(
    const Data* states,
    const Data* logweights,
    unsigned int currentIteration,
    Data* estimates
);

double integrandMeanX(const double* state, void* param);
double integrandVarX(const double* state, void* param);

double integrandMeanY(const double* state, void* param);
double integrandVarY(const double* state, void* param);

double integrandMeanCosPsi(const double* state, void* param);
double integrandVarCosPsi(const double* state, void* param);

double integrandMeanSinPsi(const double* state, void* param);
double integrandVarSinPsi(const double* state, void* param);

#endif
