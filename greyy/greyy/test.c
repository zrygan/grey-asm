#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

//
// Assembly function
//
extern void imgCvtGrayDoubleToInt(const double* src, uint8_t* dst, size_t n);

//
// Generate random image (double 0.0 to 1.0)
//
void randomizeDoubleImage(double* img, size_t n)
{
    for (size_t i = 0; i < n; i++)
        img[i] = ((int)(((double)rand() / RAND_MAX) * 100)) / 100.0;   // 0.0–1.0
}

//
// Print double matrix
//
void printDoubleMatrix(double* img, int rows, int cols)
{
    printf("DOUBLE IMAGE:\n");
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%0.2f ", img[r * cols + c]);
        }
        printf("\n");
    }
}

//
// Print integer matrix (0–255)
//
void printIntMatrix(uint8_t* img, int rows, int cols)
{
    printf("INT IMAGE (0-255):\n");
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%3d ", img[r * cols + c]);
        }
        printf("\n");
    }
}

int main()
{
    srand((unsigned)time(NULL));

    // Change these if you want
    int rows = 3;
    int cols = 4;
    size_t n = rows * cols;

    printf("%d x %d\n", rows, cols);

    // Allocate
    double* src = malloc(sizeof(double) * n);
    uint8_t* dst = malloc(sizeof(uint8_t) * n);

    // Random fill image
    randomizeDoubleImage(src, n);

    // Print source image
    printDoubleMatrix(src, rows, cols);

    // Convert using your ASM function
    imgCvtGrayDoubleToInt(src, dst, n);

    // Print output image
    printIntMatrix(dst, rows, cols);

    free(src);
    free(dst);

    return 0;
}
