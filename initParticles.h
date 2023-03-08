#include "state.h"
#include "magneticMap.h"

#ifndef INITPARTICLES_H
#define INITPARTICLES_H

// initializes all particles
void initParticles(double* logweight, State* state);

// initializes just one particle
void initParticle(double* logweight, State* state);

// compute initial logweight
double initLogLikelihood(State* state, MagneticMap* magmap);

#endif