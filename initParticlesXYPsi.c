#include "initParticlesXYPsi.h"
#include "magneticMap.h"
#include "random.h"
#include <gsl/gsl_randist.h>
#include <math.h>

extern double* obs;
extern MagneticMap* magmap;

void initParticlesXYPsi(Data* logweights, Data* states, void* params){
    // cast params from void* to its true type
    // be carefull, the compiler trusts you...
    InitXYPsiParam* initXYPsiparams = params;

    // init all particles
    unsigned int nParticles = getLen(states);
    for (unsigned int i=0; i<nParticles; ++i){
        double* state = getVal(states, i);
        initParticleXYPsi(getVal(logweights,i) ,state,initXYPsiparams);
    }
}

void initParticleXYPsi(double* logweight, double* state, const InitXYPsiParam* params){

    // Initializes a random particle position inside the map.
    // The map spatial shape is described by a collection of squares and therefore
    // the initialization is done as follow:
    // - randomly select a square
    // - create a random position inside this square
    Data* squareCenters;
    double sideLength;
    getMapShape(magmap,squareCenters, &sideLength);
    int nSquare = getLen(squareCenters);
    unsigned int k = gsl_rng_uniform_int(randomGenerator, nSquare);
    double* square = getVal(squareCenters, k);
    XYPsiSetX(state, square[0] + gsl_ran_flat(randomGenerator, -sideLength/2, sideLength/2));
    XYPsiSetY(state, square[1] + gsl_ran_flat(randomGenerator, -sideLength/2, sideLength/2));

    // Initializes a random particle orientation
    XYPsiSetPsi(state, gsl_ran_flat(randomGenerator, 0, 2*M_PI));

    // Initializes particle weight
    *logweight = logLikelihoodXYPsi(state, params);
}