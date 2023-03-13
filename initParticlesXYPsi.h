#include "stateXYPsi.h"

#ifndef INITPARTICLESXYPSI_H
#define INITPARTICLESXYPSI_H

// initializes all particles
void initParticlesXYPsi(double* logweight, StatesXYPsi* states);

// initializes just one particle
void initParticleXYPsi(double* logweight, StateXYPsi state);

// compute initial logweight
double initLogLikelihoodXYPsi(StateXYPsi state);

#endif