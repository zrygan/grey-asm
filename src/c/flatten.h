#ifndef FLATTEN_H
#define FLATTEN_H

#include "image.h"
#include <stdint.h> // for uint8_t

/**
 * A flattened DblGrey object
 *
 * @related DblGrey
 *
 */
typedef struct
{
    size_t n;       /** Product of rows and columns                                */
    uint8_t *dst;   /** Corresponding Integer Greyscale image; return of ASM code  */
    double *matrix; /** Double greyscale image; a 1D array                         */
} flattenDG;

/**
 * @brief Flattens a 2D matrix into a continuous 1D matrix for the ASM code.
 *
 * @param rows the number of rows
 * @param cols the number of columns
 * @param img the greyscale image object
 *
 * @returns a flattenDG object
 *
 */
static inline flattenDG makeFlat(int rows, int cols, DblGrey img)
{
    size_t n = rows * cols;
    uint8_t *dst = (uint8_t *)malloc(n * sizeof(uint8_t));

    double *src = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            src[i * cols + j] = img.matrix[i][j];
        }
    }

    flattenDG result;
    result.n = n;
    result.dst = dst;
    result.matrix = src;
    
    return result;
}

#endif // FLATTEN_H