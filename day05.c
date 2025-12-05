#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "common.c"

typedef unsigned long long uint64;

struct Data {
    uint64 *ranges; // each range is 2 uint64
    int num_ranges;
    uint64 *ids;
    int num_ids;
};

struct Data parse(const char* filename) {
    FILE* pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Invalid file: %s\n", filename);
        abort();
    }

    uint64 from, to;
    char row[50];
    int num_ranges = 0;
    int capacity = 50;
    uint64 *ranges = malloc(capacity * sizeof(uint64) * 2);

    int index = 0;

    while(fgets(row, sizeof row, pInput)) {
        // trim
        row[strcspn(row, "\r\n")] = 0;
        int len = strlen(row);

        // empty line means ranges are done
        if(len == 0) break;

        sscanf(row, "%lld-%lld", &from, &to);
        if(num_ranges >= capacity) {
            capacity *= 2;
            uint64 *tmp = realloc(ranges, capacity * sizeof(uint64) * 2);
            ranges = tmp;
        }
        
        ranges[index++] = from;
        ranges[index++] = to;
        num_ranges++;
    }

    capacity = 100;
    index = 0;
    uint64 * ids = malloc(capacity * sizeof(uint64));
    uint64 id = 0;
    int num_ids = 0;

    // read until end
    while(fgets(row, sizeof row, pInput)) {
        // trim
        row[strcspn(row, "\r\n")] = 0;
        sscanf(row, "%lld", &id);
        if(num_ids >= capacity) {
            capacity *= 2;
            uint64 *tmp = realloc(ids, capacity * sizeof(uint64));
            ids = tmp;
        }
        
        ids[index++] = id;
        num_ids++;
    }

    fclose(pInput);

    struct Data d = {0};
    d.ranges = ranges;
    d.num_ranges = num_ranges;
    d.ids = ids;
    d.num_ids = num_ids;
    
    return d;
}


void part1(struct Data data) {

}

void part2(struct Data data) {

}

int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s inputfile.txt\n\n", argv[0]);
        return 1;
    }

    struct timespec start, end;

    timespec_get(&start, TIME_UTC);
    struct Data d = parse(argv[1]);
    printf("%d ranges and %d ids found\n", d.num_ranges, d.num_ids);
    timespec_get(&end, TIME_UTC);
    print_time("Parsing", start, end);
    
    /*
    printf("Day 5 - Part 1: ");
    timespec_get(&start, TIME_UTC);
    part1(d);
    timespec_get(&end, TIME_UTC);
    print_time("Part 1", start, end);

    printf("Day 5 - Part 2: ");
    timespec_get(&start, TIME_UTC);
    part2(d);
    timespec_get(&end, TIME_UTC);
    print_time("Part 2", start, end);
    */
    
    free(d.ranges);
    free(d.ids);
    
    return 0;
}