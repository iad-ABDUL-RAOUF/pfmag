#include "doNothingResampling.h"

void doNothingResampling(Data* logweights __attribute__((unused)), Data* states __attribute__((unused))){
    // __attribute__((unused)) just tells to the compiler that it's normal our
    // input arguments are not used. (Otherwise you get a warning)
    
    // a resampling function that do something would typically :
    // - compute weights from logwheights using the function createNormalisedWeights (see wheight.h)
    // - perform the resampling
    // - update logweights and states accordingly
}