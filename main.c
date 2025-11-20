#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include "src/c/image.h"
#include "src/c/image_io.h"
#include "src/c/rng.h"
#include "src/c/perf.h"
#include "src/c/flatten.h"

extern void imgCvtGrayDoubleToInt(const double* src, uint8_t* dst, size_t n);

int main()
{
    srand(time(NULL));

    // Create a test DblGrey image
    const unsigned int ROWS = 3;
    const unsigned int COLS = 4;
    DblGrey *dbImg = makeDG(COLS, ROWS);
    
    randpopDG(dbImg);
    
    // DISPLAY FOR DEBUGGING
    printf("\nDEBUGGING: DOUBLE GREYSCALE IMAGE\n");
    displayDG(*dbImg);
    
    // Flatten the 2D matrix and prepare for assembly call
    flattenDG flat = makeFlat(ROWS, COLS, *dbImg);

    startTime(&stime, &freq);

    // Call assembly function
    imgCvtGrayDoubleToInt(flat.matrix, flat.dst, flat.n);

    endTime(&stime, &etime, &freq, &diff);
    
    printf("\nDEBUGGING: INTEGER GREYSCALE IMAGE (ASM)\n");
    displayFlat(flat);
    
    // Cleanup
    free(flat.matrix);
    free(flat.dst);
    free(dbImg->matrix);
    free(dbImg);
    
    return 0;
}