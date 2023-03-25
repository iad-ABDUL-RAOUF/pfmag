#include "data.h"

#ifndef WRITEPARTICLES_H
#define WRITEPARTICLES_H


// write states and wheights into two csv inside the directory
// "particlesDirname". Each filename also contain the iteration number
// (so filenames are unique for each iteration)
void writeParticles(
    const Data* states,
    const Data* logweights,
    const char* dirname,
    unsigned int iteration
);

#endif
