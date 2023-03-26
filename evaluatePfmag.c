#include "data.h"
#include "csv.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Evaluate the estimates computed from the particle filtering against the true poses (ground truth)
int main(int argc, char** argv){
    printf("-------in evaluatePfmag-------\n");
    // read paramters
    if (argc!=3){
        printf("in evaluatePfmag.c, wrong number of inputs\n");
        exit(EXIT_FAILURE);
    }
    char* estimatesFilename = argv[1];
    printf("estimatesFilename = %s\n", estimatesFilename);
    char* groundtruthFilename = argv[2];
    printf("groundtruthFilename = %s\n", groundtruthFilename);

    // load inputs
    printf("load inputs\n");
    Data* estimates = readCsv(estimatesFilename,",");
    Data* groundtruth = readCsv(groundtruthFilename,",");

    // check inputs
    unsigned int nEstimates = getLen(estimates);
    unsigned int nGt = getLen(groundtruth);
    if (nEstimates != nGt){
        printf("ground truth trajectory has a different number of states than the estimated trajectory : wrong files ?\n");
        exit(EXIT_FAILURE);
    }

    printf("compare ground truth with estimates\n");
    // get final estimates
    double meanX = getVal(estimates,nEstimates-1)[0];
    double varX = getVal(estimates,nEstimates-1)[1];
    double meanY = getVal(estimates,nEstimates-1)[2];
    double varY = getVal(estimates,nEstimates-1)[3];
    double meanCosPsi = getVal(estimates,nEstimates-1)[4];
    double meanSinPsi = getVal(estimates,nEstimates-1)[6];
    double estimatedPsi = atan2(meanSinPsi,meanCosPsi);
    
    // get final true pose
    double trueX = getVal(groundtruth, nEstimates-1)[0];
    double trueY = getVal(groundtruth, nEstimates-1)[1];
    double truePsi = getVal(groundtruth, nEstimates-1)[2];

    destroyData(estimates);
    destroyData(groundtruth);

    bool hasConverged = false;
    // By definition, convergence happens if the particle cloud is small enough at the last timestep
    // Particle cloud size is inferred through x and y variances of this cloud.
    if (varX < 1.0 && varY < 1.0){
        hasConverged = true;
    }
    printf("convergence (no:0, yes:1) : %d\n", hasConverged); // O means no convergence, 1 means convergence

    // compute and print errors
    double diffX = meanX-trueX;
    double diffY = meanY-trueY;
    printf("final position error : %f (meter)\n", sqrt(diffX*diffX + diffY*diffY));
    double diffPsi = estimatedPsi-truePsi;
    double diffPsi = fmod(diffPsi-M_PI, 2*M_PI) + M_PI; // compute angle in [-pi, pi)
    printf("final orientation error : %f (degrees)\n", (diffPsi)*180/M_PI);
    
    // Beware that it is possible to get simulatenously a convergence and a large error.
    // The filter can converge toward a wrong position and orientation.
    // Actually, if the error is big, it is better if the filter did not
    // converged, so the user knows it cannot trust the output.
    printf("-------the end-------\n");
    return EXIT_SUCCESS;
}