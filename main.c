#include "initParticles.h"
#include "moveParticles.h"
#include "state.h"
#include "magneticMap.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    
    printf("load parameters\n");
    // number of particle
    int N = atoi(argv[1]);
    printf("N = %d\n", N);
    // odometry filename
    char* odomfn = argv[2];
    // magnetic measure filename
    char* magmeasfn = argv[3];
    // magnetic map filename
    char* magmapfn = argv[4];

    // load inputs
    MagneticMap magmap; // TODO
    // TODO typdedef odometry et magnetometry (juste un elem) et les nommer u et y. Les liste peuvent avoir des nom plus explicite (odometries et magmeasurements)

    // initializes particles
    // logweights contains the logarithm of weights. It is better than
    // using directly the weights because of numerical precision issues 
    double* logweights = malloc(N*sizeof(double));
    State* states = malloc(N*sizeof(State));

    initParticles(logweights, states);

    // - initvaleur
    //      - initpoid

    // moveParticles
    // - updateValeur
    //      - updatePoid

    // resample

    printf("-------the end-------\n");
    return 0;
}