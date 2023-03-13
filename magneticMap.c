// You don't have to look at what is inside magneticMap.c. It is outside
// the scope of this project.

// Still reading ?!?! No limits to your curiosity ?

// Here is a code for the magnetic map that is somewhat real
// and somewhat fake.
// I could not provide you the original one as it is the property
// of my company (CEA)

// It takes as input a file of magnetic values sampled on a grid
// of position from a real map. Then it interpolates the values
// in between. Because covariance interpolation isn't straitforward,
// I used fake covariances.

// But don't worry the magnetic measurement of the dataset I gave
// you are simulated to be coherent with this half fake map...
// These simulated data respect perfectly the map model which is
// never the case with real data. Thus you should actually get better 
// results compared to if you used the real thing. Enjoy !

#include "data.h"

struct MagneticMap{
    Data* positionGrid;
    Data* magVals;
    double* inMapFakeCov;
    double* outMapFakeCov;
};
