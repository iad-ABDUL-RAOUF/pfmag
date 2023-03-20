#include <gsl/gsl_rng.h>

#ifndef RANDOM_H
#define RANDOM_H

// global variable generator, so you don't have to pass it everywhere in
// function arguments
extern gsl_rng* randomGenerator;

// See the official documentation for available probability distribution :
// uniform, gaussian, multinomial...
// https://www.gnu.org/software/gsl/doc/html/randist.html

#endif