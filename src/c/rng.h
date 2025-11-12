#ifndef RNG_H
#define RNG_H

#include <stdlib.h>

inline unsigned int randint()
{
    return (unsigned int) ((rand() % 255) + 1 );
}

inline double randdbl()
{
    return (rand() % 99999 + 1) * 0.00001;
}

#endif // RNG_H