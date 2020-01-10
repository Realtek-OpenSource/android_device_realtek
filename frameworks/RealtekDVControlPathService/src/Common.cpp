#include <time.h>
#include <stdio.h>
#include "Common.h"

#define MAX_LOG_BUFFER (512)

static struct timespec g_warning_counter = {0};

void StartElapseTime(struct timespec &start)
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

float EndElapseTime(struct timespec &start)
{
    struct timespec end;

    clock_gettime(CLOCK_MONOTONIC, &end);

    struct timespec diff;

    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        diff.tv_sec = end.tv_sec - start.tv_sec - 1;
        diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        diff.tv_sec = end.tv_sec - start.tv_sec;
        diff.tv_nsec = end.tv_nsec - start.tv_nsec;
    }

    int time = diff.tv_sec * 10000 + diff.tv_nsec / 100000;
    return (time / 10.0f);
}

void WarningPerSec(int sec, const char *p_str, ...)
{
    float time = EndElapseTime(g_warning_counter);

    if (time > sec)
    {
        va_list list;
        char buffer[MAX_LOG_BUFFER] = {0};

        va_start(list, p_str);
        vsnprintf(buffer, MAX_LOG_BUFFER, p_str, list);
        va_end(list);

        RTKDVLOG(p_str, buffer);
    }

    StartElapseTime(g_warning_counter);
}

