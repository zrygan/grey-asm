#ifndef RNG_H
#define RNG_H

#include <stdlib.h>

/**
 * @brief Generates a random integer within the range of [0,255]
 * 
 */
inline unsigned int randint()
{
    return (unsigned int) ((rand() % 255) + 1 );
}

/**
 * @brief Generates a random double-precision floating point number within the range of
 * [0.00000, 0.99999]
 * 
 */
inline double randdbl()
{
    return (rand() % 99999 + 1) * 0.00001;
}

#endif // RNG_H