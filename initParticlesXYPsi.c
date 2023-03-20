#include "initParticlesXYPsi.h"
#include "magneticMap.h"
#include "random.h"
#include <math.h>

extern double* obs;
extern MagneticMap* magmap;

void initParticlesXYPsi(Data* logweights, Data* states, void* params){
    // cast params from void* to its true type
    // be carefull, the compiler trusts you...
    InitXYPsiParam* initXYPsiparams = (InitXYPsiParam*) params;

    // init all particles
    unsigned int nParticles = getLen(states);
    for (unsigned int i=0; i<nParticles; ++i){
        double* state = getVal(states, i);
        initParticleXYPsi(getVal(logweights,i) ,state,initXYPsiparams);
    }
}

void initParticleXYPsi(double* logweight, double* state, InitXYPsiParam* params){

    // Initializes a random particle position inside the map.
    // The map spatial shape is described by a collection of squares and therefore
    // the initialization is done as follow:
    // - randomly select a square
    // - create a random position inside this square
    Data* squareCenters;
    double sideLength;
    getMapShape(magmap,squareCenters,&sideLength);
    int nSquare = (int)getLen(squareCenters);
    unsigned int k = (unsigned int)uniformInt(0,nSquare);
    double* square = getVal(squareCenters,k);
    XYPsiSetX(state,square[0] + uniform(-sideLength/2,sideLength/2));
    XYPsiSetY(state,square[1] + uniform(-sideLength/2,sideLength/2));

    // Initializes a random particle orientation
    XYPsiSetPsi(state,uniform(0,2*M_PI));

    // Initializes particle weight
    *logweight = logLikelihoodXYPsi(state, params);
}