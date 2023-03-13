#include "stateXYPsi.h"
#include "magneticMap.h"

#ifndef MOVEPARTICLESXYPSI_H
#define MOVEPARTICLESXYPSI_H

extern 

// update all particles
void moveParticlesXYPsi(double* logweight, StatesXYPsi* states);

// update just one particle
void moveParticleXYPsi(double* logweight, StateXYPsi state);

// compute lodweight increment
double logLikelihoodXYPsi(StateXYPsi state, MagneticMap* magmap);

#endif