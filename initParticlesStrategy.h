#include "data.h"

#ifndef INITPARTICLESSTRATEGY_H
#define INITPARTICLESSTRATEGY_H

// InitParticlesStrategy define the interface of an initParticles
// function. It allows you to switch between different implementation
// in main.c without any code modification (in particular, without
// dirty copying and pasting and/or commenting out blocks of code...)

// see the commentary inside "resamplingStrategy.h" for
// a detailed explanation
typedef void (*InitParticlesStrategy)(double* logweight, Data* states, void* params);

#endif