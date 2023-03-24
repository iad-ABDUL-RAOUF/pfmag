#include "writeParticles.h"
#include "weight.h"
#include "csv.h"
#include <stdlib.h>

#define FILENAMEMAXCHAR 1024
#define SUBDIR "particles/"

void writeParticles(const Data* states, const Data* logweights, const char* rootDirname, unsigned int iteration){
    // write states
    char statesFilename[FILENAMEMAXCHAR];
    double ret = snprintf(statesFilename, sizeof(statesFilename), "%s%sstates%d.csv", rootDirname, SUBDIR, iteration);
    if(ret < 0 || sizeof(statesFilename) <= ret){
        printf("in writeParticles error while converting into string or statesFilename is too long\n");
        exit(EXIT_FAILURE);
    };
    writeCsv(statesFilename, states, "# particle states");

    // write weights
    char wheightsFilename[FILENAMEMAXCHAR];
    ret = snprintf(wheightsFilename, sizeof(statesFilename), "%s%sweights%d.csv", rootDirname, SUBDIR, iteration);
    if(ret < 0 || sizeof(statesFilename) <= ret){
        printf("in writeParticles, wheightsFilename is too long\n");
        exit(EXIT_FAILURE);
    };
    Data* weights = createNormalisedWeights(logweights);
    writeCsv(wheightsFilename, weights, "# particle weights");
    destroyData(weights);
}
