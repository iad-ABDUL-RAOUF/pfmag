#include "initParticlesXYPsi.h"
#include "magneticMap.h"
#include "magneticObservation.h"

extern Mag obs;
extern MagneticMap* magmap;

void initParticlesXYPsi(double* logweight, Data* states){
    unsigned int nParticles = getLen(states);
    for (unsigned int i=0; i<nParticles; ++i){
        StateXYPsi state = getVal(states, i);
        initXYPsiParticle(&logweight[i],state);
    }
}