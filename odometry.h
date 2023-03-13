#include "data.h"

#ifndef ODOMETRY_H
#define ODOMETRY_H

typedef Data Odoms;
typedef double* Odom;

// getters
// (u is a standard notation for odometry input)
double OdomGetUx(Odom u);
double OdomGetUy(Odom u);
double OdomGetUpsi(Odom u);

#endif