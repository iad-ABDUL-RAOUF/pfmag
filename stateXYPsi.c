#include "stateXYPsi.h"

StatesXYPsi* createStatesXYPsi(unsigned int len){
    StatesXYPsi* states = createData(3, len);
}

double XYPsiGetX(const double* state){
    return state[0];
}

double XYPsiGetY(const double* state){
    return state[1];
}

double XYPsiGetPsi(const double* state){
    return state[2];
}

void XYPsiSetX(double* state, double x){
    state[0] = x;
}

void XYPsiSetY(double* state, double y){
    state[1] = y;
}

void XYPsiSetPsi(double* state, double psi){
    state[2] = psi;
}
