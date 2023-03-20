#include "data.h"

#ifndef ODOMETRY_H
#define ODOMETRY_H

// getters
// (u is a standard notation for odometry input)
double odomGetUx(const double* odom);
double odomGetUy(const double* odom);
double odomGetUpsi(const double* odom);

#endif