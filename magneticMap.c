// You don't have to look at what is inside magneticMap.c. It is outside
// the scope of this project.

// Still reading ?!?! No limits to your curiosity ?

// Here is a code for the magnetic map that is somewhat real
// and somewhat fake.
// I could not provide you the original one as it is the property
// of my company (CEA)

// It takes as input a file of magnetic values sampled on a grid
// of position from a real map. Then it interpolates the values
// in between. The uncertainty model is also simplified.

// But don't worry the magnetic measurement of the dataset I gave
// you are simulated to be coherent with this half fake map...
// These simulated data respect perfectly the map model which is
// never the case with real data. Thus you should actually get better 
// results compared to if you used the real thing. Enjoy !

#include "magneticMap.h"
#include "csv.h"
#include "data.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define LINEMAXCHAR 1024

// Bellow are some private function signatures (not in .h as you should
// not include them anywhere else).
// I'am hiding them here to not expose you to more things in this already
// big project

// read the parameter line in file
void readParametersFromFile(FILE* file, MagneticMap* magmap);
// read data (without the paramters)
void readMapData(FILE* file, MagneticMap* magmap);
// indexer return the index of the element or nxstep*nystep if it is out
// of bound
unsigned int indexer(const MagneticMap* magmap, int i, int j);
// interpolate scalar values
double interpolate(
    double val11, double val12, double val21, double val22,
    double x1, double x2, double y1, double y2,
    double x, double y
);
// interpolate vectorial values
void interpolateVector(
    unsigned int dim,
    double* valout,
    const double* val11,
    const double* val12,
    const double* val21,
    const double* val22,
    double x1, double x2, double y1, double y2,
    double x, double y
);
double quotient(double x, double x0, double step);

struct MagneticMap{
    double xmin;
    double ymin;
    double step;
    unsigned int nxstep;
    unsigned int nystep;
    Data* magVals; // magnetic values of the rectangle map
    double* magStd; // standard deviations of the rectangle map 
    Data* positionGrid; // position of the discrete map 
};

// function implementations start here

MagneticMap* createMagneticMap(const char* filename){
    
    // open file
    FILE *file = fopen(filename,"r");
    if (file == NULL){
        printf("createMagneticMap could not open file");
        exit(EXIT_FAILURE);
    }

    // skip the first line (assumes it is header commentary)
    char row[LINEMAXCHAR];
    fgets(row, LINEMAXCHAR, file);
    MagneticMap* magmap = malloc(sizeof(MagneticMap));

    // read the parameter line
    readParametersFromFile(file, magmap);

    // skip the next line (assumes it is again a commentary)
    fgets(row, LINEMAXCHAR, file);

    // read the rest of the data
    readMapData(file, magmap);

    return magmap;
}

void destroyMagneticMap(MagneticMap* magmap){
    destroyData(magmap->positionGrid);
    destroyData(magmap->magVals);
    free(magmap->magStd);
}

void predict(const MagneticMap* magmap, const double* position, double* mag, double* std_mag){
    // Interpolate values known on a discret grid of position
    // This is in no way a realistic map model. It is designed specifically
    // for this course's project
    
    int ix = quotient(position[0], magmap->xmin, magmap->step);
    int iy = quotient(position[1], magmap->ymin, magmap->step);

    double x1 = magmap->xmin + ix*magmap->step;
    double x2 = magmap->xmin + (ix+1)*magmap->step;
    double y1 = magmap->ymin + iy*magmap->step;
    double y2 = magmap->ymin + (iy+1)*magmap->step;

    // indices of elements used for interpolation
    unsigned int i11 = indexer(magmap,ix,iy);
    unsigned int i12 = indexer(magmap,ix,iy+1);
    unsigned int i21 = indexer(magmap,ix+1,iy);
    unsigned int i22 = indexer(magmap,ix+1,iy+1);

    // interpolation of map uncertainty
    *std_mag = interpolate(
        magmap->magStd[i11],
        magmap->magStd[i12],
        magmap->magStd[i21],
        magmap->magStd[i22],
        x1, x2, y1, y2,
        position[0], position[1]
    );

    // interpolation of magnetic vectors
    interpolateVector(
        3,
        mag,
        getVal(magmap->magVals,i11),
        getVal(magmap->magVals,i12),
        getVal(magmap->magVals,i21),
        getVal(magmap->magVals,i22),
        x1, x2, y1, y2,
        position[0], position[1]
    );
}

void getMapShape(const MagneticMap* magmap, Data** squareCenters, double* squareSideLength){
    *squareCenters = magmap->positionGrid;
    *squareSideLength = magmap->step;
}

void readParametersFromFile(FILE* file, MagneticMap* magmap){
    char row[LINEMAXCHAR];
    if(fgets(row, LINEMAXCHAR, file) == NULL){
        printf("readParametersFromFile found no parameters in file");
        exit(EXIT_FAILURE);
    }
    unsigned int dim = getNValues(row, ",");
    if(dim != 5){
        printf("readParametersFromFile found a wrong number of element in row");
        exit(EXIT_FAILURE);
    }
    double values[dim]; 
    parseRow(row, ",", values);
    magmap->xmin = values[0];
    magmap->ymin = values[1];
    magmap->step = values[2];
    magmap->nxstep = values[3];
    magmap->nystep = values[4];
}

void readMapData(FILE* file, MagneticMap* magmap){
    Data* mapData = readCsvFile(file, ",");
    if (getDim(mapData) != 7){
        printf("readMapData found a wrong number of element by row");
        exit(EXIT_FAILURE);
    }
    
    // Create a "rectangle" map that approximately cover the rectangle area :
    // [xmin, xmin+nxstep*step] X [ymin, ymin+nystep*step]
    // It has nxstep*nystep+1 elements because the last one is used
    // as a default value at any position outside the rectangle.
    unsigned int lenRectangleMap = (magmap->nxstep)*(magmap->nystep)+1;
    magmap->magVals = createData(3,lenRectangleMap);
    magmap->magStd = malloc((lenRectangleMap)*sizeof(double));

    // fill in the rectangle map with default values
    for (unsigned int i = 0; i<lenRectangleMap; ++i){
        setScalarVal(magmap->magVals, i, 0.0);
        magmap->magStd[i] = 25.5; // it should be a parameter...
    }

    unsigned int lenMapData = getLen(mapData);
    // fill in the rectangle map with values read from the input file
    for (unsigned int i = 0; i<lenMapData; ++i){
        double* inputval = getVal(mapData,i);
        double* inputposition = inputval;
        double* inputmag = &inputval[2];
        double inputmagStd = inputval[5];

        int ix = quotient(inputposition[0], magmap->xmin, magmap->step);
        int iy = quotient(inputposition[1], magmap->ymin, magmap->step);
        unsigned int index = indexer(magmap,ix,iy);

        setVal(magmap->magVals, index, inputmag);
        magmap->magStd[i] = inputmagStd;
        setVal(magmap->positionGrid, i, inputposition);
    }
    destroyData(mapData);
}

unsigned int indexer(const MagneticMap* magmap, int ix, int iy){
    if (ix < 0 || (magmap->nxstep <= (unsigned int)ix) || iy<0 ||(magmap->nystep <= (unsigned int)iy)){
        return magmap->nxstep * magmap->nystep;  // out of bound output
    }
    else{
        return (ix * magmap->nystep + iy);
    }
}

double interpolate(
    double val11, double val12, double val21, double val22,
    double x1, double x2, double y1, double y2,
    double x, double y
){
    // implement Bilinear interpolation
    // https://en.wikipedia.org/wiki/Bilinear_interpolation
    return (val11*(x2-x)*(y2-y)
            +val21*(x-x1)*(y2-y)
            +val12*(x2-x)*(y-y1)
            +val22*(x-x1)*(y-y1))
            /((x2-x1)*(y2-y1));
}

void interpolateVector(
    unsigned int dim,
    double* valout,
    const double* val11,
    const double* val12,
    const double* val21,
    const double* val22,
    double x1, double x2, double y1, double y2,
    double x, double y
){
    for (unsigned int d = 0; d<dim; ++d){
        valout[d] = interpolate(val11[d],val12[d],val21[d],val22[d],x1,x2,y1,y2,x,y);
    }
}

double quotient(double x, double x0, double step){
    return floor((x-x0)/step);
}
