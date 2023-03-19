#include "stateXYPsi.h"
#include "magneticMap.h"

#ifndef MOVEPARTICLESXYPSI_H
#define MOVEPARTICLESXYPSI_H

extern double* odom;
extern double* obs;
extern MagneticMap* magmap;

typedef struct MoveXYPsiParam{
    // standard deviation of the odometry magnetometer measurments error
    // modeled as a gaussian. For simplicity, errors on mx,my,mz are assumed
    // to be independant and to have the same standard deviation (iid)
    double std_obs;
    // standard deviation of the odometry random perturbation 
    double std_ux;
    double std_uy;
    double std_upsi;
    // magnetometer bias are assumed to be knonw here
    double bx;
    double by;
    double bz;
}MoveXYPsiParam;

// update all particles
void moveParticlesXYPsi(double* logweight, StatesXYPsi* states, void* params);

// update just one particle
void moveParticleXYPsi(double* logweight, StateXYPsi state, MoveXYPsiParam* params);

// compute lodweight increment
double logLikelihoodXYPsi(StateXYPsi state, MoveXYPsiParam* params);

#endif