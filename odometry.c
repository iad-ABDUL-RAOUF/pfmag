#include "odometry.h"

double odomGetUx(double* odom){
    return odom[0];
}

double odomGetUy(double* odom){
    return odom[1];
}

double odomGetUpsi(double* odom){
    return odom[2];
}
