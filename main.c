#include <stdio.h>
#include <time.h>
#include "src/c/image.h"
#include "src/c/image_io.h"
#include "src/c/rng.h"
#include "src/c/perf.h"

void printDetails()
{
    printf("===== DETAILS =====\n");
    printf("time: %10.8lf\n", diff);
}

int main()
{
    srand(time(NULL));

    startTime(&stime, &freq);

    /* ADD code here*/

    endTime(&stime, &etime, &freq, &diff);
    printDetails();    
    
    return 0;
}