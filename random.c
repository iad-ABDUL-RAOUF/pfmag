#include "random.h"

#include <stdlib.h>
#include <math.h>


double uniform(double min, double max){
    return min + (max-min) * ((double)rand()) / ((double)RAND_MAX +1.0);
}

int uniformInt(int min, int max){
    return (int) floor(uniform(min, max));
}

double gaussian(double mu, double sigma){
    double x1 = uniform(0,1);
    double x2 = uniform(0,1);
    double x3 = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2);
    x3 = x3*sigma + mu;
    return x3;
}