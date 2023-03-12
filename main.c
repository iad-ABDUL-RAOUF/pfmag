#include "initParticles.h"
#include "moveParticles.h"
#include "doNothingResampling.h"
#include "resamplingStrategy.h"
#include "state.h"
#include "magneticMap.h"
#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    
    printf("load parameters\n");
    int N = atoi(argv[1]); // number of particle
    printf("N = %d\n", N);
    // odometry, magnetic measurements and magnetic map filenames
    char* odometryfn = argv[2];
    char* observationfn = argv[3];
    char* magmapfn = argv[4];
    char* resamplingName = argv[5];
    ResamplingStrategy resampling;
    if (strcmp(resamplingName,"noResampling") == 0){
        resampling = doNothingResampling;
    }

    // load inputs
    MagneticMap magmap; // TODO read file
    Data odometry = readCsv(odometryfn);
    Data magobs = readCsv(observationfn);    

    // A good practice would be to assert that all inputs are sane. For instance
    // one could check that N is strictly positive, and that there is exactly one
    // more magnetic observation data compared to the number of odometry data.

    // In the following, the current observation y and odometry u are used as global
    // variables inside the init and move functions...

    // initializes particles
    unsigned int t = 0; // time
    double* y = getVal(magobs, t); 
    // logweights contains the logarithm of weights. It is advantageous because of
    // numerical precision issues 
    double* logweights = malloc(N*sizeof(double));
    State* states = malloc(N*sizeof(State));
    initParticles(logweights, states);

    // move particles for each time step
    double* u;
    unsigned int nObs = getLen(magobs);
    for(t = 1; t<nObs; ++t)
        // odometry u is not used in initialization, therefore there is a shift
        // of minus one compared to the observation index t.
        u = getVal(odometry, t-1);
        y = getVal(magobs, t);
        moveParticle(logweights, states);

        // resample
        resampling(logweights,states);

        // TODO write particles

    // TODO write outputs in csv file format
    
    free(logweights);
    free(states);
    destroyData(odometry);
    destroyData(magobs);

    printf("-------the end-------\n");
    return 0;
}