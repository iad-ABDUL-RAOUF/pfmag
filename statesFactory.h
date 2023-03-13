#include "data.h"

#ifndef STATESFACTORY_H
#define STATESFACTORY_H

// StateFactory define the interface of a function that creates
// our particle states. It allows you to switch between different states
// in main.c without any code modification (in particular, without
// dirty copying and pasting and/or commenting out blocks of code...)

// I called this pattern a "Factory" because it "creates" something but
// it uses actually the same programmation tricks as described in
// "resamplingStrategy.h"

typedef Data* (*StatesFactory)(unsigned int len);

#endif