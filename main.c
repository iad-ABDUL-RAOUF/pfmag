#include "odometry.h"

#include "statesFactory.h"
#include "initParticlesXYPsi.h"
#include "initParticlesStrategy.h"
#include "moveParticlesXYPsi.h"
#include "moveParticlesStrategy.h"

#include "doNothingResampling.h"
#include "resamplingStrategy.h"
#include "stateXYPsi.h"
#include "magneticMap.h"
#include "csv.h"
#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// some global variables used by init particle and by
// move particle functions...
double* odom;
double* obs;
MagneticMap* magmap;

int main(int argc, char** argv){
    
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Setup everything according to user input and load data.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    printf("load parameters\n");
    int N = atoi(argv[1]); // number of particle
    printf("N = %d\n", N);
    char* odometryFilename = argv[2];
    char* observationFilename = argv[3];
    char* magmapFilename = argv[4];
    char* stateName = argv[5];
    char* resamplingName = argv[6];

    // Here functions are variables !!
    // You can choose which function to select at
    // runtime depending on user inputs.
    StatesFactory createState;
    InitParticlesStrategy initParticles;
    MoveParticlesStrategy moveParticles;
    void* moveParams;
    void* initParams;
    if(strcmp(stateName,"XYPsi")){
        createState = createStatesXYPsi;
        initParticles = initParticlesXYPsi;
        moveParticles = moveParticlesXYPsi;
        MoveXYPsiParam mparam = {.std_obs=0.3, .std_ux=0.1, .std_uy=0.1, .std_upsi=0.024,
                            .bx=9.0, .by=-2.3, .bz=4.8};
        InitXYPsiParam iparam = mparam; // cast possible because its actually the same type (typedef)
        moveParams = (void*) &mparam;
        initParams = (void*) &iparam;
    }
    // add other possibility if you work on the option 2 of this course project ;)
    else{
        
        printf("unkown state type");
        exit(EXIT_FAILURE);
    }

    ResamplingStrategy resampling;
    if (strcmp(resamplingName,"noResampling") == 0){
        resampling = doNothingResampling;
    }
    // add other possibility here to use other resampling strategy (see preliminary and
    // option 1 of this course project)
    else{
        printf("unkown resampling algorithm");
        exit(EXIT_FAILURE);
    }

    // load inputs
    magmap = createMagneticMap(magmapFilename);
    Data* odometry = readCsv(odometryFilename,",");
    Data* magobs = readCsv(observationFilename,",");

    // TODO set random seed (for reproductibility)

    // A good practice would be to assert that all inputs are sane. For instance
    // one could check that N is strictly positive, and that there is exactly one
    // more magnetic observation data compared to the number of odometry data.

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Finally ! Everything is loaded. Particle filtering starts from here !
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // initializes particles
    unsigned int t = 0; // time
    obs = getVal(magobs, t); 
    // logweights contains the logarithm of weights. It is advantageous because of
    // numerical precision issues.
    double* logweights = malloc(N*sizeof(double));
    Data* states = createState(N);
    initParticles(logweights, states, initParams);

    // move particles for each time step
    unsigned int nObs = getLen(magobs);
    for(t = 1; t<nObs; ++t)
        // odometry u is not used in initialization, therefore there is a shift
        // of minus one compared to the observation index t.
        odom = getVal(odometry, t-1);
        obs = getVal(magobs, t);
        moveParticles(logweights, states, moveParams);

        // resample
        resampling(logweights,states);

        // TODO create some functoins to convert between weight and logweights in logweight.h
        // and see where it should go

        // TODO write particles in csv file format

    // TODO write estimates in csv file format
    
    destroyData(odometry);
    destroyData(magobs);
    free(logweights);
    destroyData(states);
    destroyMagneticMap(magmap);
    

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Compare the particle filter estimates with the ground thruth.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // TODO plutot à metre dans un autre executable
    

    printf("-------the end-------\n");
    return EXIT_SUCCESS;
}