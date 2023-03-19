#include "writeParticles.h"
#include "weight.h"
#include "csv.h"

#define FILENAMEMAXCHAR 1000
#define SUBDIR "particles/"

void writeParticles(const Data* states, const Data* logweights, const char* rootDirname, unsigned int iteration){
    // write states
    char statesFilename[FILENAMEMAXCHAR];
    snprintf(statesFilename, sizeof(statesFilename), "%s%sstates%d.csv", rootDirname, SUBDIR, iteration);
    writeCsv(statesFilename, states, "# particle states line by line at a given timestep");

    // write weights
    char wheightsFilename[FILENAMEMAXCHAR];
    snprintf(wheightsFilename, sizeof(statesFilename), "%s%sweights%d.csv", rootDirname, SUBDIR, iteration);
    Data* weights = createNormalisedWeights(logweights);
    writeCsv(wheightsFilename, weights, "# weights at a given timestep");
    destroyData(weights);
}

// void mkdirParticles(const char* rootDirname){
//     char particlesDirname[FILENAMEMAXCHAR];
//     snprintf(particlesDirname, sizeof(particlesDirname), "%s%s",rootDirname, SUBDIR);
//     // TODO mkdir
// } // TODO remove