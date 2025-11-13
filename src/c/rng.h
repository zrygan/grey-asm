#ifndef RNG_H
#define RNG_H

#include <stdlib.h>

/**
 * @brief Generates a random integer within the range of [0,255].
 *
 */
static inline unsigned int randint()
{
    return (unsigned int)((rand() % 255) + 1);
}

/**
 * @brief Generates a random double-precision floating point number within the range of
 * [0.00000, 0.99999].
 *
 */
static inline double randdbl()
{
    return (rand() % 99999 + 1) * 0.00001;
}

/**
 * @brief Populates a DblGrey structure with random numbers.
 *
 * @param img A pointer to a DblGrey structure.
 *
 * @related randdbl()
 *
 */
static inline void randpopDG(DblGrey *img)
{
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            img->matrix[i][j] = randdbl();
        }
    }
}

/**
 * @brief Populates a IntGrey structure with random numbers.
 *
 * @param img A pointer to a IntGrey structure.
 *
 * @related randint()
 *
 */
static inline void randpopIG(IntGrey *img)
{
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            img->matrix[i][j] = randint();
        }
    }
}

#endif // RNG_H