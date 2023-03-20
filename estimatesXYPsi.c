#include "estimatesXYPsi.h"
#include "estimates.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Data* createEstimatesXYPsi(unsigned int len){
    Data* estimates = createData(8, len);
    return estimates;
}

void computeEstimatesXYPsi(
    const Data* states,
    const Data* logweights,
    unsigned int currentIteration,
    Data* estimates
){
    Data* weights = createNormalisedWeights(logweights);
    unsigned int dim = getDim(estimates);
    if (dim != 8){
        printf("estimate has a wrong dimention. Expects 8 : mX, vX, mY, vY, mCosPsi, vCosPsi, mSinPsi, vSinPsi");
        exit(EXIT_FAILURE);
    }
    if (currentIteration >= getLen(estimates)){
        printf("currentIteration exceeds estimate length");
        exit(EXIT_FAILURE);
    }
    double currentEstimate[dim];
    currentEstimate[0] = integrate(states, weights, integrandMeanX, NULL);
    currentEstimate[1] = integrate(states, weights, integrandVarX, &currentEstimate[0]);
    currentEstimate[2] = integrate(states, weights, integrandMeanY, NULL);
    currentEstimate[3] = integrate(states, weights, integrandVarY, &currentEstimate[2]);
    currentEstimate[4] = integrate(states, weights, integrandMeanCosPsi, NULL);
    currentEstimate[5] = integrate(states, weights, integrandVarCosPsi, &currentEstimate[4]);
    currentEstimate[6] = integrate(states, weights, integrandMeanSinPsi, NULL);
    currentEstimate[7] = integrate(states, weights, integrandVarSinPsi, &currentEstimate[6]);
    setVal(estimates, currentIteration, currentEstimate);
    destroyData(weights);
}

double integrandMeanX(const double* state, void* param){
    return XYPsiGetX(state);
}
double integrandVarX(const double* state, void* voidmX){
    double* mX = voidmX;
    double x = XYPsiGetX(state);
    return (x-*mX)*(x-*mX);
}

double integrandMeanY(const double* state, void* param){
    return XYPsiGetY(state);
}
double integrandVarY(const double* state, void* voidmY){
    double* mY = voidmY;
    double y = XYPsiGetY(state);
    return (y-*mY)*(y-*mY);
}

double integrandMeanCosPsi(const double* state, void* param){
    return cos(XYPsiGetPsi(state));
}
double integrandVarCosPsi(const double* state, void* voidmCosPsi){
    double* mCosPsi = voidmCosPsi;
    double cosPsi = cos(XYPsiGetPsi(state));
    return (cosPsi-*mCosPsi)*(cosPsi-*mCosPsi);
}

double integrandMeanSinPsi(const double* state, void* param){
    return sin(XYPsiGetPsi(state));
}

double integrandVarSinPsi(const double* state, void* voidmSinPsi){
    double* mSinPsi = voidmSinPsi;
    double sinPsi = sin(XYPsiGetPsi(state));
    return (sinPsi-*mSinPsi)*(sinPsi-*mSinPsi);
}
