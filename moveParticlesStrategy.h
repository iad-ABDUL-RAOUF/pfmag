#include "data.h"

#ifndef MOVEPARTICLESSTRATEGY_H
#define MOVEPARTICLESSTRATEGY_H

// MoveParticlesStrategy define the interface of an moveParticles
// function. It allows you easily to switch between different
// implementation in main.c. This design patter is called strategy
// http://www.adampetersen.se/Patterns%20in%20C%203,%20STRATEGY.pdf
// Also include a void* parameter because various implementation will each have
// their own parameter set. void* will allow you to use any paramter type.
// Be carefull, using void* the compiler has no information on the input type
// and cannnot detects bugs for you.
typedef void (*MoveParticlesStrategy)(Data* logweights, Data* states, void* params);

#endif