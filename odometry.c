#include "odometry.h"

double odomGetUx(const double* odom){
    return odom[0];
}

double odomGetUy(const double* odom){
    return odom[1];
}

double odomGetUpsi(const double* odom){
    return odom[2];
}
