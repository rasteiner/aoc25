#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef unsigned long long uint64;
typedef bool (*validator)(uint64 num);

bool check_num_double(uint64 num) {
    uint64 d = (int)log10((double)num) + 1;
    uint64 de = (uint64)pow(10, d / 2);
    return num / de == num % de;
}

bool check_num_any(uint64 num) {
    int len = (int)log10((double)num) + 1;

    char str[20];
    sprintf(str, "%lld", num);

    for(int substrlen = 1; substrlen <= len / 2; substrlen++) {
        if(len % substrlen > 0)continue;
        int numslices = len / substrlen;
        
        for(int i = 0; i < substrlen; i++) {
            for(int y = 1; y < numslices; y++) {
                if(str[i] != str[i + y * substrlen]) {
                    goto nextslice;
                }
            }
        }

        return true;

        nextslice: continue;
    }

    return false;
}

void run_with(const char* filename, validator fn) {
    FILE *pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Error opening input file");
        return;
    }

    uint64 from = 0;
    uint64 to = 0;
    uint64 total = 0;

    while(!feof(pInput) && fscanf(pInput, "%lld-%lld,", &from, &to)) {
        for(uint64 num = from; num <= to; num++) {
            if(fn(num)) {
                total += num;
            }
        }
    }
    fclose(pInput);

    printf("Total is %lld\n", total);
}

void part1(const char* filename) {
    run_with(filename, check_num_double);
}

void part2(const char* filename) {
    run_with(filename, check_num_any);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s inputfile.txt\n\n", argv[0]);
        return 1;
    }

    printf("Day 2 - part 1: ");
    part1(argv[1]);

    printf("Day 2 - part 2: ");
    part2(argv[1]);

    return 0;
}