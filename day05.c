#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "common.c"


struct Data {
    uint64 *ranges; // each range is 2 uint64
    int num_ranges;
    uint64 *ids;
    int num_ids;
};


struct Data parse(char* input) {
    uint64 from, to;

    int num_ranges = 0;
    int capacity = 50;
    uint64 *ranges = malloc(capacity * sizeof(uint64) * 2);

    // the next index for "things to insert"
    int index = 0;
    
    // point to the first char
    char *c = input;

    // go until we encounter the \0 terminator (or more probable the loop break below on a double new line)
    while(*c) {
        if (*c == '\r') {
            // skip
            c++;
            continue;
        }
        if (*c == '\n') {
            // if the next char is again \r or \n we have an empty line
            // todo: bounds check? in theory there's ~always~ an empty line in the input files. 
            char next = *(c+1);
            if(next == '\n' || next == '\r') {
                // then we have finished the ranges section
                c++;
                break;
            }

            // otherwise skip
            c++;
        }
        
        // read a number
        from = parse_num(&c);
        if(from == 0) {
            fprintf(stderr, "improbable range start 0\n");
            exit(1);
        }

        // read a "-"
        if(*c != '-') {
            fprintf(stderr, "expected '-' after %lld\n", from);
        }
        c++;

        // read a number
        to = parse_num(&c);
        if(to == 0) {
            fprintf(stderr, "improbable range end 0\n");
            exit(1);
        }
        
        // store 
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
    while(*c) {
        // skip newlines chars
        if (*c == '\r' || *c == '\n') {
            c++;
            continue;
        }
    
        // abort on invalid number
        id = parse_num(&c);
        if(id == 0) {
            fprintf(stderr, "improbable id 0\n");
            exit(1);
        }

        if(num_ids >= capacity) {
            capacity *= 2;
            uint64 *tmp = realloc(ids, capacity * sizeof(uint64));
            ids = tmp;
        }

        ids[index++] = id;
        num_ids++;
    }

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
    char * input = read_all(argv[1]);
    struct Data d = parse(input);
    timespec_get(&end, TIME_UTC);
    printf("%d ranges and %d ids found\n", d.num_ranges, d.num_ids);
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