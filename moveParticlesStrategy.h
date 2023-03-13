#include "data.h"

#ifndef MOVEPARTICLESSTRATEGY_H
#define MOVEPARTICLESSTRATEGY_H

// MoveParticlesStrategy define the interface of an moveParticles
// function. It allows you to switch between different implementation
// in main.c without any code modification (in particular, without
// dirty copying and pasting and/or commenting out blocks of code...)

// see the commentary inside "resamplingStrategy.h" for
// a detailed explanation
typedef void (*MoveParticlesStrategy)(double* logweight, Data* states);

#endif