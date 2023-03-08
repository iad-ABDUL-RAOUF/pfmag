#ifndef MAGNETICMAP_H
#define MAGNETICMAP_H

// Here is a code for the magnetic map that is somewhat real
// and somewhat fake.

// It takes as input a file of magnetic values sampled on a grid
// of position from a real map. Then it interpolates the values
// in between. Because covariance interpolation isn't straitforward,
// I used fake covariances.

// I could not provide you the original map code for several reason :
// - it is the property of my company (CEA)
// - it is in C++
// - it is too long to redevelop in C for this project

// But don't worry the magnetic measurement of the dataset I gave
// you are simulated to be coherent with this half fake map...
// These simulated data respect perfectly the map model which is
// never the case with real data. Thus you should actually get better 
// results compared to if you used the real thing. Enjoy !

typedef struct MagneticMap {
// TODO
} MagneticMap;

#endif
