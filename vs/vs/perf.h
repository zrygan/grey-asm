#ifndef PERF_H
#define PERF_H

#include <stdio.h>

#if defined(_WIN32) && defined(_WIN64)

#include <windows.h>
LARGE_INTEGER stime, etime, freq;
double diff;

static inline void startTime(LARGE_INTEGER* stime, LARGE_INTEGER* freq)
{
    QueryPerformanceFrequency(freq);

    QueryPerformanceCounter(stime);
}

static inline void endTime(LARGE_INTEGER* stime, LARGE_INTEGER* etime, LARGE_INTEGER* freq, double* diff)
{
    QueryPerformanceCounter(etime);

    *diff = (double)(etime->QuadPart - stime->QuadPart) / freq->QuadPart;
}

#else

#include <time.h>
time_t stime, etime, diff;

static inline void startTime(time_t* stime)
{
    time(stime);
}

static inline void endTime(time_t* stime, time_t* etime, time_t* diff)
{
    time(etime);
    *diff = difftime(*stime, *etime);
}

#endif

#endif // PERF_H