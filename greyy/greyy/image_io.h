#ifndef UTIL_H
#define UTIL_H

#include "image.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief Displays the IntGrey to the standard output.
 *
 * @param img the IntGrey structure to display.
 *
 */
static inline void displayIG(IntGrey img)
{
    for (unsigned int i = 0; i < img.height; i++)
    {
        for (unsigned int j = 0; j < img.width; j++)
        {
            printf("%3d ", img.matrix[i][j]);
        }

        printf("\n");
    }
}

/**
 * @brief Populates the IntGrey from user input.
 *
 * @param img the IntGrey structure to populate via user input.
 * @param message the message to display for each scanf call.
 *
 * @note I don't think we need to use this, for testing purposes only.
 *
 */
static inline void inputIG(IntGrey img, char* message)
{
    const char* msg = (message == NULL) ? "" : message;

    for (unsigned int i = 0; i < img.height; i++)
    {
        for (unsigned int j = 0; j < img.width; j++)
        {
            printf("%s", msg);
            scanf_s("%d", &img.matrix[i][j]);
        }
    }
}

/**
 * @brief Displays the IntGrey to the standard output.
 *
 * @param img the IntGrey structure to display.
 *
 */
static inline void displayDG(DblGrey img)
{
    for (unsigned int i = 0; i < img.height; i++)
    {
        for (unsigned int j = 0; j < img.width; j++)
        {
            printf("%3.2lf ", img.matrix[i][j]);
        }

        printf("\n");
    }
}

/**
 * @brief Populates the DblGrey from user input.
 *
 * @param img the IntGrey structure to populate via user input.
 * @param message the message to display for each scanf call.
 *
 * @note I don't think we need to use this, for testing purposes only.
 *
 */
static inline void inputDG(DblGrey img, char* message)
{
    const char* msg = (message == NULL) ? "" : message;

    for (unsigned int i = 0; i < img.height; i++)
    {
        for (unsigned int j = 0; j < img.width; j++)
        {
            printf("%s", msg);
            scanf_s("%lf", &img.matrix[i][j]);
        }
    }
}

#endif // UTIL_H