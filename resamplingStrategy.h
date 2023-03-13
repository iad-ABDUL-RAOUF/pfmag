#include "data.h"

#ifndef RESAMPLINGSTRATEGY_H
#define RESAMPLINGSTRATEGY_H

// Here we use a design pattern called a "strategy"
// http://www.adampetersen.se/Patterns%20in%20C%203,%20STRATEGY.pdf
// It will allow you to easily switch between resampling algorithms
// and therefore to test many of them with minimal code modification.
// The general idea is to define a common interface to all the possible
// resamppling method and then to provide specific implementation
// elsewhere.

// ResamplingStrategy is the type of a function pointer
// taking as argument (double* logweights, State* states) and
// returning void
// An example of specific implementation is the "doNothingResampling"
// And an example of usage is found in the main. 
typedef void (*ResamplingStrategy)(double* logweights, Data* states);

// note that this interface is limited as it does not allow the usage
// of additionnal parameters. However it should be good enough for this
// project. Feel free to improve it.

#endif