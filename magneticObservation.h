#include "data.h"

#ifndef MAGNETICOBSERVATION_H
#define MAGNETICOBSERVATION_H

typedef Data Mags;
typedef double* Mag;

// getters
double MagGetMx(Mag m);
double MagGetMy(Mag m);
double MagGetMz(Mag m);

#endif