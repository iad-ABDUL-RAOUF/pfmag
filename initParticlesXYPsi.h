#include "moveParticlesXYPsi.h"
#include "stateXYPsi.h"
#include "data.h"

#ifndef INITPARTICLESXYPSI_H
#define INITPARTICLESXYPSI_H

// Here init paramters are the same as move parameters but it doesn't has to be
typedef MoveXYPsiParam InitXYPsiParam;

// initializes all particles
void initParticlesXYPsi(Data* logweights, StatesXYPsi* states, void* params);

// initializes just one particle
void initParticleXYPsi(double* logweight, double* state, const InitXYPsiParam* params);

#endif