#include "data.h"

#ifndef STATEXYPSI_H
#define STATEXYPSI_H

typedef Data StatesXYPsi;

// create states
StatesXYPsi* createStatesXYPsi(unsigned int len);

// getters and setters to avoid index confusion

// getters

double XYPsiGetX(const double* state);
double XYPsiGetY(const double* state);
double XYPsiGetPsi(const double* state);

// setters

void XYPsiSetX(double* state, double x);
void XYPsiSetY(double* state, double y);
void XYPsiSetPsi(double* state, double psi);

#endif