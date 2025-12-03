#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef unsigned long long uint64;

void part1(const char* filename) {
    FILE *pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Error opening input file");
        return;
    }

    char row[110];
    long total = 0;

    while(fgets(row, sizeof row, pInput)) {
        row[strcspn(row, "\n")] = 0;
        int len = strlen(row);
        if(len < 2) continue;

        short onei = 0;
        char one = row[onei];
        
        // char one must be the biggest number between row[0] and row[len - 2]
        // char two must ne the biggest number between row[onei + 1] and row[len - 1]

        // find char one
        for(short i = 1; i <= len - 2; i++) {
            if(row[i] > one) {
                one = row[i];
                onei = i;
            }
        }
                
        char two = row[onei + 1];

        // find char two
        for(short i = onei + 2; i < len; i++) {
            if(row[i] > two) {
                two = row[i];
            }
        }
        
        short num = (one - 48) * 10 + (two - 48);

        total += num;
    }

    printf("Total: %ld\n", total);

    fclose(pInput);
}

uint64 quick_pow10(short n)
{
    static uint64 pow10[15] = {
        1, 10, 100, 1000, 10000, 
        100000, 1000000, 10000000, 100000000, 1000000000,
        10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000
    };

    return pow10[n]; 
}

void part2(const char* filename) {
    FILE *pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Error opening input file");
        return;
    }

    char row[110];
    uint64 total = 0;


    while(fgets(row, sizeof row, pInput)) {
        row[strcspn(row, "\n")] = 0;
        int len = strlen(row);

        if(len < 12) continue;

        short firstIndex = 0;
        for(short battery = 0; battery < 12; battery++) {
            short lastIndex = len - 12 + battery;

            char best = row[firstIndex];
            int bestI = firstIndex;

            for(short i = firstIndex + 1; i <= lastIndex; i++) {
                if(row[i] > best) {
                    best = row[i];
                    bestI = i;
                }
            }
            
            firstIndex = bestI + 1;

            total += (best - 48) * quick_pow10(11 - battery);
        }

    }

    printf("Total: %lld\n", total);

    fclose(pInput);
}

void printtime(struct timespec start, struct timespec end) {
    printf("Took %.3f ms\n",(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s inputfile.txt\n\n", argv[0]);
        return 1;
    }

    struct timespec start, end;
        
    printf("Day 3 - part 1: ");
    timespec_get(&start, TIME_UTC);
    part1(argv[1]);
    timespec_get(&end, TIME_UTC);
    printtime(start, end);

    printf("Day 3 - part 2: ");
    timespec_get(&start, TIME_UTC);
    part2(argv[1]);
    timespec_get(&end, TIME_UTC);
    printtime(start, end);

    return 0;
}