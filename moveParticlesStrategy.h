#include "data.h"

#ifndef MOVEPARTICLESSTRATEGY_H
#define MOVEPARTICLESSTRATEGY_H

// MoveParticlesStrategy define the interface of an moveParticles
// function. It allows you easily to switch between different
// implementation in main.c 

// Similar to "resamplingStrategy.h" but it also include a void*
// parameter. Because various implementation will each have their own parameter set,
// void* will allow you to use any paramter type.
// Be carefull, using void* is unsafe because the compiler has no information on
// the input type and cannnot detect bugs for you.
typedef void (*MoveParticlesStrategy)(Data* logweights, Data* states, void* params);

#endif