#include <stdio.h>
#include <time.h>
#include "../src/c/image.h"
#include "../src/c/image_io.h"
#include "../src/c/rng.h"
#include "../src/c/perf.h"

#define COLS 1000
#define ROWS 1000
#define NTEST 1000

// ===== PERFORMANCE TESTING ======================================
// This code tests the C file without the ASM file.
// See `comp_perf_test.c` for the comprehensive performance testing.
// ================================================================

int main()
{
    srand(time(NULL));

    startTime(&stime, &freq);

    for (int i = 0; i < NTEST; i++)
    {
        DblGrey *db1 = makeDG(COLS, ROWS);
        randpopDG(db1);
    }

    endTime(&stime, &etime, &freq, &diff);

    printf("time: %10.8lf\n",
           diff);

    printf("appr: %10.8lf\t(n = 5; NTEST, COLS, ROWS = 1000)\n",
           8.97473742);

    printf("diff: %10.7lf\t(time - appr)\n",
           diff - 8.97473742);
}