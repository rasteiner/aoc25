#include <stdio.h>
#include <time.h>

void print_time(const char* name, struct timespec start, struct timespec end) {
    printf("\e[0;90m \300 %s took %.3lfms\e[0m\n", name, (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0);
}
