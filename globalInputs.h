#include "magneticMap.h"

#ifndef GLOBALINPUTS_H
#define GLOBALINPUTS_H

// If needed here is how you declare global variables. Include this file
// in every .c file where those varaibles are needed.
// You cannot define variables in header. So you add the keyword 'extern' to 
// say that this is not et definitition but a declaration.
// Then, somewhere in your program, you will have to define them. (done in the
// main.c here)
// Here is a nice forum post about global variables :
// https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files



// Global variables used by initParticle and by moveParticle functions but read
// in the main (sensor inputs and magmap)

extern double* odom;
extern double* obs;
extern MagneticMap* magmap;

#endif