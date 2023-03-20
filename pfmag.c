#include "odometry.h"
#include "initParticlesXYPsi.h"
#include "initParticlesStrategy.h"
#include "moveParticlesXYPsi.h"
#include "moveParticlesStrategy.h"
#include "estimatesXYPsi.h"
#include "estimates.h"
#include "writeParticles.h"
#include "doNothingResampling.h"
#include "resamplingStrategy.h"
#include "stateXYPsi.h"
#include "magneticMap.h"
#include "csv.h"
#include "data.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some global variables used by initParticle and by moveParticle functions...
// Input odometry
double* odom;
// Input magnetic vector (observation)
double* obs;
// Input magnetic map of the area
MagneticMap* magmap;

int main(int argc, char** argv){
    
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Setup everything according to user input and load data.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    printf("load parameters\n");
    // number of particle
    int nParticles = atoi(argv[1]);
    printf("nParticles = %d\n", nParticles);
    char* odometryFilename = argv[2];
    char* observationFilename = argv[3];
    char* magmapFilename = argv[4];
    char* stateName = argv[5];
    char* resamplingName = argv[6];
    // output directory name ending by '/'
    char* outputDirname = argv[7];
    // There is a lot of input variables here, you might want to
    // load them by other means (e.g. from configuration file)

    // load inputs
    magmap = createMagneticMap(magmapFilename);
    Data* odometry = readCsv(odometryFilename,",");
    Data* magobs = readCsv(observationFilename,",");
    unsigned int nObs = getLen(magobs);

    // In the following functions are also variables !
    // You can choose which function to select at
    // runtime depending on user inputs.

    // contain a list of particle values
    Data* states;
    // function to initialize particles
    InitParticlesStrategy initParticles;
    // initialization parameters
    void* initParams;
    // function to update (move) particles
    MoveParticlesStrategy moveParticles;
    // move parameters
    void* moveParams;
    // store the successive state estimation ('average' of all particles)
    Data* estimates;
    // function to compute the state estimation
    ComputeEstimates computeEstimates;
    // OPTION2 : the state is chosen here. 
    if(strcmp(stateName,"XYPsi")){
        states = createStatesXYPsi(nParticles);
        initParticles = initParticlesXYPsi;
        moveParticles = moveParticlesXYPsi;
        MoveXYPsiParam mparam = {.std_obs=0.3, .std_ux=0.1, .std_uy=0.1, .std_upsi=0.024,
                            .bx=9.0, .by=-2.3, .bz=4.8};
        InitXYPsiParam iparam = mparam;
        moveParams = (void*) &mparam;
        initParams = (void*) &iparam;
        estimates = createEstimatesXYPsi(nObs);
        computeEstimates = computeEstimatesXYPsi;
    }
    else{
        printf("unkown state type");
        exit(EXIT_FAILURE);
    }

    // fucntion to resample particles
    ResamplingStrategy resampling;
    // PRELIMINARY,OPTION1 : the resampling strategy si choosen here
    if (strcmp(resamplingName,"noResampling") == 0){
        resampling = doNothingResampling;
    }
    else{
        printf("unkown resampling algorithm");
        exit(EXIT_FAILURE);
    }

    // create output directory and base filename
    // mkdirParticles(outputDirname); // TODO supprimer (aussi de .c et .h) c'est le bash qui va creer le dossier (?)

    // TODO set random seed (for reproductibility)

    // A good practice would be to assert that all inputs are sane. For instance
    // one could check that nParticles is strictly positive, that there is
    // exactly one more magnetic observation data compared to the number of
    // odometry data, etc.

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Finally ! Everything is loaded. Particle filtering starts from here !
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // initializes particles
    unsigned int t = 0; // time
    obs = getVal(magobs, t);
    // logweights contains the logarithm of weights. It is advantageous because
    // of numerical precision issues.
    Data* logweights = createData(1,nParticles);
    initParticles(logweights, states, initParams);
    resampling(logweights,states);
    
    // compute etimation of the state and write particles
    computeEstimates(states, logweights, t, estimates);
    writeParticles(states, logweights, outputDirname, t);

    // move particles for each time step
    for(t = 1; t<nObs; ++t)
        // odometry u is not used in initialization, therefore there is a shift
        // of minus one compared to the observation index t.
        odom = getVal(odometry, t-1);
        obs = getVal(magobs, t);
        moveParticles(logweights, states, moveParams);

        // resample
        resampling(logweights,states);

        // compute etimation of the state and write particles
        computeEstimates(states, logweights, t, estimates);
        writeParticles(states, logweights, outputDirname, t); // TODO virer du timer

    // write estimates in csv file format
    char estimatesFilename[1024];
    int ret = snprintf(estimatesFilename, sizeof(estimatesFilename), "%sestimates.csv", outputDirname);
    if(ret < 0 || sizeof(estimatesFilename) <= ret){
        printf("in main, outputDirname is too long");
        exit(EXIT_FAILURE);
    };
    writeCsv(estimatesFilename, estimates, "# state estimation based on particles after each observation");

    // clean up memory : every "create" or "malloc" should correspond to a
    // "destroy" or a "free".
    destroyData(odometry);
    destroyData(magobs);
    destroyData(logweights);
    destroyData(states);
    destroyMagneticMap(magmap);

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Compare the particle filter estimates with the ground thruth.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // TODO plutot à metre dans un autre executable ? qui lirait juste les estimates et la verité terrain

    printf("-------the end-------\n");
    return EXIT_SUCCESS;
}