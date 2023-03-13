#ifndef MAGNETICMAP_H
#define MAGNETICMAP_H

// Here is a magnetic map. You can interact with it using the provided
// functions

// I used the FIRST-CLASS ADT design pattern to hide implementation details
// http://adampetersen.se/Patterns%20in%20C%201.pdf

typedef struct MagneticMap MagneticMap;

MagneticMap* readMagneticMapFile(char* filename);

// "position" is the position x,y,z at which one requieres to consult the map
// of the magnetic field
// magVec is the magnetic field value mx,my,mz returned by the map
// magCov is the 3x3 covariance matrix associated to the returned values. It 
// represent an uncertainty. The smaller the covariance is the more confident
// we are.
predict(double* position, double* magVec, double* magCov);



#endif
