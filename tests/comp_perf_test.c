#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include "../src/c/image.h"
#include "../src/c/image_io.h"
#include "../src/c/rng.h"
#include "../src/c/convert.h"
#include "../src/c/perf.h"
#include "../src/c/flatten.h"

extern void imgCvtGrayDoubleToInt(const double *src, uint8_t *dst, size_t n);

// ===== PERFORMANCE TESTING ======================================
// Comprehensive performance testing.
// ================================================================

#define REPS  20 // n. of times the performance test repeats
#define NTEST 4
int main()
{
    srand(time(NULL));
    
    printf("Starting performance test...\n");
    
    // Test sizes: 10x10, 100x100, 1000x1000 + Stress Test
    int sizes[NTEST][2] = {{10, 10}, {100, 100}, {1000, 1000}, {10000, 10000}};
    double res_c[NTEST], res_asm[NTEST];
    
    for (int e = 0; e < NTEST; e++)
    {
        const unsigned int ROWS = sizes[e][0];
        const unsigned int COLS = sizes[e][1];
        
        printf("\nTest %d: %dx%d (%d pixels)\n", e, ROWS, COLS, ROWS*COLS);
        double asm_times[REPS], c_times[REPS];
        
        for (int i = 0; i < REPS; i++)
        {
            printf("  Rep %d/%d...\n", i+1, REPS);
            DblGrey *dbImg = makeDG(COLS, ROWS);
            randpopDG(dbImg);
            

            flattenDG flat = makeFlat(ROWS, COLS, *dbImg);
        
            // Time ASM file
            startTime(&stime, &freq);
            imgCvtGrayDoubleToInt(flat.matrix, flat.dst, flat.n);
            endTime(&stime, &etime, &freq, &diff);
            asm_times[i] = diff;
            
            // Time C file
            startTime(&stime, &freq);
            IntGrey *cResult = c_imgCvtGrayDoubleToInt(*dbImg);
            endTime(&stime, &etime, &freq, &diff);
            c_times[i] = diff;

            // Cleanup
            free(flat.matrix);
            free(flat.dst);
            for (int j = 0; j < ROWS; j++) {
                free(dbImg->matrix[j]);
                free(cResult->matrix[j]);
            }
            free(dbImg->matrix);
            free(cResult->matrix);
            free(dbImg);
            free(cResult);
        }

        // get average of each x_times
        double c_avg = 0.0, asm_avg = 0.0;
        for (int t = 0; t < REPS; t++){
            c_avg += c_times[t];
            asm_avg += asm_times[t];
        }

        res_c[e] = c_avg / REPS;
        res_asm[e] = asm_avg / REPS;
    }
    
    
    printf("\n===== RESULTS =====\n");
    for (int e = 0; e < NTEST; e++)
    {
        int w = sizes[e][0];
        int h = sizes[e][1];
        printf("Test %d (%dx%d): ASM = %5.8f sec | C = %5.8f sec | Speedup = %.2fx\n", 
               e, w, h, res_asm[e], res_c[e], res_c[e]/res_asm[e]);
    }

    return 0;
}