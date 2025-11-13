#include <stdio.h>
#include <time.h>
#include "../c/image.h"
#include "../c/image_io.h"
#include "../c/rng.h"
#include "../c/perf.h"

#define COLS 1000
#define ROWS 1000
#define NTEST 1000

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