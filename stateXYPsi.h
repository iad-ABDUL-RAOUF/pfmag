#include "data.h"

#ifndef STATEXYPSI_H
#define STATEXYPSI_H

typedef Data StatesXYPsi;
typedef double* StateXYPsi;

// create states
StatesXYPsi* createStatesXYPsi(unsigned int len);

// get state components
double XYPsiGetX(StateXYPsi state);
double XYPsiGetY(StateXYPsi state);
double XYPsiGetPsi(StateXYPsi state);

// set state components
void XYPsiSetX(StateXYPsi state, double x);
void XYPsiSetY(StateXYPsi state, double y);
void XYPsiSetPsi(StateXYPsi state, double psi);

#endif