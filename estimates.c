#include "estimates.h"

double integrate(
    const Data* states,
    const Data* weights,
    const Integrand integrand,
    void* params
){
    double integral = 0;
    unsigned int nParticles = getLen(states);
    for (unsigned int i = 0; i<nParticles; ++i){
        integral += *getVal(weights,i) * integrand(getVal(states,i), params);
    }
    return integral;
}