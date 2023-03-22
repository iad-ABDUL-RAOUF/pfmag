#include "moveParticlesXYPsi.h"
#include "random.h"
#include "odometry.h"
#include <gsl/gsl_randist.h>
#include <math.h>

void moveParticlesXYPsi(Data* logweights, StatesXYPsi* states, void* params){
    // cast params from void* to its true type
    // be carefull, the compiler trusts you...
    MoveXYPsiParam* moveXYPsiparams = params;

    // move all particles
    unsigned int nParticles = getLen(states);
    for (unsigned int i=0; i<nParticles; ++i){
        double* state = getVal(states, i);
        moveParticleXYPsi(getVal(logweights,i),state,moveXYPsiparams);
    }
}

void moveParticleXYPsi(double* logweight, double* state, const MoveXYPsiParam* params){
    double ux = odomGetUx(odom) + gsl_ran_gaussian(randomGenerator, params->std_ux);
    double uy = odomGetUy(odom) + gsl_ran_gaussian(randomGenerator, params->std_uy);
    double upsi = odomGetUpsi(odom) + gsl_ran_gaussian(randomGenerator, params->std_upsi);

    double x = XYPsiGetX(state);
    double y = XYPsiGetY(state);
    double psi = XYPsiGetPsi(state);

    // move particles according to the odometry input, with small random
    // perturbation to explore the values around (each particles has the same odom input but
    // different random perturbation)

    // mathematical odometry model :
    // odometry input (ux,uy,upsi) is the displacement observed through the robot wheels
    // motion.
    // state = (x,y,psi) is the current state of the robot (accroding to this particle)
    // The new orientation is psi+upsi
    // Because the translation (ux,uy) is expressed in a local coordinate frame, we first
    // rotate it by the angle psi and then apply it to x and y.
    // Hence the formula :
    XYPsiSetX(state, cos(psi)*ux-sin(psi)*uy + x);
    XYPsiSetY(state, sin(psi)*ux+cos(psi)*uy + y);
    XYPsiSetPsi(state, psi+upsi);

    *logweight += logLikelihoodXYPsi(state, params);
}

double logLikelihoodXYPsi(double* state, const MoveXYPsiParam* params){
    
    // Here we compare the observation made by the magnetometer with
    // the value of the magnetic map at the position of the given particles
    // The higher the difference is, the lower the particle likelihood
    // become. 
    
    double position[2] = {XYPsiGetX(state), XYPsiGetY(state)};
    double mapMagVec[3];
    double std_magmap;
    predict(magmap, position, mapMagVec, &std_magmap);

    // The magnetometer observation obs is done in the robot coordinate frame, whereas
    // the magnetic vector read from the map is in the map frame. And thereis a rotation
    // of angle psi between them.
    // Therefore, to compare them we need to put them in the same frame (here we choose
    // the sensor frame).
    double psi = XYPsiGetPsi(state);
    double mx = cos(psi)*mapMagVec[0] + sin(psi)*mapMagVec[1];
    double my = -sin(psi)*mapMagVec[0] + cos(psi)*mapMagVec[1];
    double mz = mapMagVec[2];

    // also measurement are corrupted by a bias b = (bx,by,bz).
    // instead of correcting obs, we corrupt mapMagVec with the same bias.
    mx += params->bx;
    my += params->by;
    mz += params->bz;

    // errors between map and measured values are
    double ex = obs[0] - mx;
    double ey = obs[1] - my;
    double ez = obs[2] - mz;

    // Now we compute the loglikelihood update of the particle based on the error.
    // Hence we need to know the law followed by (ex,ey,ez) 
    
    // We assume our magnetometer noise follows a gaussian law on each component.
    // Same for the map error.
    // Therefore the error on each component is guassian whose parameter (mean, std),
    // are easily computed.

    // We can also drop all additive constants in front of the logweight increment.
    // Indeed if all logweight are updatated by the same constant, it changes
    // nothing after renormalisation of all weight such that their sum is equal to 1.0.  
    
    // Hence (after formula reduction) the loglikelihhod increment is :
    double var = (params->std_obs) * (params->std_obs) + (std_magmap*std_magmap);
    return -0.5 * ((ex*ex + ey*ey + ez*ez)/var + 3 * log(var));
}