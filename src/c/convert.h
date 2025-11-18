#ifndef CONVERT_H
#define CONVERT_H

#include "image.h"
#include <math.h>

#define ITOD_CONST 0.392156863

/**
 * @brief Convert a greyscale unsigned integer to greyscale double precision floating-point.
 * That is, convert integer [0, 255] to double [0.0, 1.0]
 * 
 * @param i The greyscale unsigned integer to convert
 * 
 * @return The double equivalent of the greyscale value {i}
 * 
 * @note I don't think we need to use this, for testing purposes only.
 * 
 * @details
 *      Formula:
 *           ceil(i / 255.0 * 100) / 100
 *      rounds to infty the 2 significant figures of i / 255
 *       
 *      This formula is not very performant (it has 4 FLOPs), for an n-by-n matrix this becomes
 *      4n^2 FLOP!
 *      
 *      We can reduce this by defining the 255.0 * 100 as a contant.
 *
 * @related ITOD_CONST
 */
static inline double itod(unsigned int i)
{
    return (double)ceil(i * ITOD_CONST) / 100;
}

/**
 * @brief Convert a greyscale double to greyscale unsigned integer.
 * That is, double [0.0, 1.0] to integer [0, 255]
 * 
 * @param d The greyscale double to convert (expected range: 0.0 to 1.0)
 * 
 * @return The unsigned integer equivalent of the greyscale value {d}
 * 
 * @note Uses round-to-nearest, ties-to-even (banker's rounding)
 */
static inline unsigned int dtoi(double d)
{
    return (unsigned int)lrint(d * 255.0); 
}

/**
 * @brief Convert a DblGrey structure to its equivalent IntGrey structure.
 *
 * @param img The DblGrey structure to convert to IntGrey.
 *
 * @return an IntGrey structure.
 *
 */
static inline IntGrey *c_imgCvtGrayDoubleToInt(DblGrey img)
{
    IntGrey *ret = makeIG(img.width, img.height);
    
    for (int i = 0; i < ret->height; i++){
        for (int j = 0; j < ret->width; j++)
            ret->matrix[i][j] = dtoi(img.matrix[i][j]);
    }

    return ret;
}

#endif // CONVERT_H