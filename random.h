// Some usefull random functions
// Low random quality. Do not use for professional purposes

#ifndef RANDOM_H
#define RANDOM_H

// real uniform distriubtion on [min, max)
double uniform(double min, double max);
// uniform distribution on {min, min+1, ..., max-1}
int uniformInt(int min, int max);
// gaussian distriubtion of mean mu and statndard deviation sigma
double gaussian(double mu, double sigma);

#endif