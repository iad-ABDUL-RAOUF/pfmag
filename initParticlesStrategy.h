#include "data.h"

#ifndef INITPARTICLESSTRATEGY_H
#define INITPARTICLESSTRATEGY_H


// InitParticlesStrategy define the interface of an initParticles
// function. See MoveParticlesStrategy.h for more explanation.
typedef void (*InitParticlesStrategy)(Data* logweights, Data* states, void* params);

#endif