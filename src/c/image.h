#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

#define MAX_H 1000
#define MAX_W 1000

/**
 * Integer grayscale image
 */
typedef struct
{
    unsigned int **matrix; /** A 2D matrix of unsigned integers */
    unsigned int width;    /** Width of the matrix              */
    unsigned int height;   /** Height of the matrix             */
} IntGrey;

/**
 * 64-bit floating point greyscale image
 */
typedef struct
{
    double **matrix;     /** A 2D matrix of double */
    unsigned int width;  /** Width of the matrix   */
    unsigned int height; /** Height of the matrix  */
} DblGrey;

/**
 * @brief This creates an integer greyscale image (2D-matrix of unsigned integers) given a specific
 * width and height.
 *
 * @param width: an unsigned integer that denotes the number of columns.
 * @param height: an unsigned integer that denotes the number of rows.
 *
 * @return a IntGrey struct.
 *
 * @note Assumed width and height make sense.
 */
inline IntGrey *makeIG(unsigned int width, unsigned int height)
{
    IntGrey *img = (IntGrey *)malloc(sizeof(IntGrey));
    img->width = width;
    img->height = height;

    img->matrix = malloc(sizeof(unsigned int) * height);
    for (int i = 0; i < height; i++)
        img->matrix[i] = malloc(sizeof(unsigned int) * width);

    return img;
}

/**
 * @brief This created an 64-bit floating-point greyscale image (2D-matrix of doubles) given a
 * specific width and height.
 *
 *
 * @param width: an unsigned integer that denotes the number of columns.
 * @param height: an unsigned integer that denotes the number of rows.
 *
 * @return an DblGrey struct.
 *
 * @note Assumed width and height make sense.
 */
inline DblGrey *makeDG(unsigned int width, unsigned int height)
{
    DblGrey *img = (DblGrey *)malloc(sizeof(DblGrey));
    img->width = width;
    img->height = height;

    img->matrix = malloc(sizeof(double) * height);
    for (int i = 0; i < height; i++)
        img->matrix[i] = malloc(sizeof(double) * width);

    return img;
}

#endif // IMAGE_h