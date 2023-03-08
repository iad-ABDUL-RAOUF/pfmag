#include "state.h"
#include "magneticMap.h"

#ifndef MOVEPARTICLES_H
#define MOVEPARTICLES_H

// update all particles
void moveParticles(double* logweight, State* state);

// update just one particle
void moveParticle(double* logweight, State* state);

// compute lodweight increment
double logLikelihood(State* state, MagneticMap* magmap);

#endif