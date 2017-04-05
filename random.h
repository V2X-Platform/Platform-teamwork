#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED


#include <stdlib.h>

double random_0to1()
{
    unsigned uSeed = 453676;
    srand(uSeed);
    return rand()%(999+1)/(double)(1000);
}

#endif // RANDOM_H_INCLUDED
