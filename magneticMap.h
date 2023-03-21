#include "data.h"

#ifndef MAGNETICMAP_H
#define MAGNETICMAP_H

// Here is a magnetic map. You can interact with it using the provided
// functions bellow : create, destroy, predict, ...

// I used the FIRST-CLASS ADT design pattern to hide implementation details
// http://adampetersen.se/Patterns%20in%20C%201.pdf

typedef struct MagneticMap MagneticMap;

// expect a .magmap file with :
// - a one line commentary
// a second line with paramter values separated by comma :
// - xmin,ymin,step,nxstep,nystep
// - again a commentary
// The remainder of the file contain the rest of the data :
// - px, py, mx, my, mz, std
MagneticMap* createMagneticMap(const char* filename);

void destroyMagneticMap(MagneticMap* magmap);

// - "position" references the position x,y at which one requieres to consult the map
// - "mag" references the magnetic field value mx,my,mz returned by the map
// - "std_mag" references a scalar representing the standard deviation of the gaussian
// uncertainty associated to the returned values (the map is never perfect,
// there is always an error compared to reality). It is a simplified uncertainty
// model that assumes mx,my and mz are i.i.d (otherwise you would have a 3x3
// covariance matrix)
void predict(const MagneticMap* magmap, const double* position, double* mag, double* std_mag);

// The shape of the area covered by the map is approximated as an union of squares
// - "squareCenters" contain the centers x0,y0,x1,y1,... where xi,yi is the center of
// the i-th sqare
// - "squareSideLength" reference a scalar representing the side length of all squares.
void getMapShape(const MagneticMap* magmap, Data** squareCenters, double* squareSideLength);



#endif
