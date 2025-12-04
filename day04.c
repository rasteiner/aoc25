#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "common.c"

struct Field {
    int h, w;
    bool *field;
};

struct Field parse(const char* filename) {
    char data[256][256];
    char row[256];
    int h = 0, w = 0;

    FILE* pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Invalid file: %s\n", filename);
        abort();
    }
    
    while(fgets(row, sizeof row, pInput)) {
        // trim
        row[strcspn(row, "\r\n")] = 0;    
        int len = strlen(row);
        if(len < 3) continue;
        if(len > w) w = len;
        memcpy(data[h], row, len);
        h += 1;
    }
    fclose(pInput);

    bool *field = malloc(h * w * sizeof(bool));

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            field[y * w + x] = data[y][x] == '@';
        }
    }
    
    struct Field r = {
        h: h,
        w: w,
        field: field,
    };

    return r;
}


void part1(struct Field data) {
    int h = data.h;
    int w = data.w;
    
    int count = 0;

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            if(data.field[y * w + x] == false) {
                continue;
            }

            int free = 0;
            for(int dx = -1; dx <= 1; dx++) for(int dy = -1; dy <= 1; dy++) {
                if(dy == 0 && dx == 0)continue;
                int gx = x + dx;
                int gy = y + dy;
                if(gy < 0 || gy >= h || gx < 0 || gx >= w || data.field[gy * w + gx] == false) free++;
            }

            if(free > 4) {
                count++;
            }
        }
    }

    printf("Count: %d\n", count);
}

void part2(struct Field data) {
    int h = data.h;
    int w = data.w;
    
    int count = 0;

    bool* copy = malloc(h * w * sizeof(bool));
    
    int removed = 0;

    do {
        removed = 0;

        for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++) {
                if(data.field[y * w + x] == false) {
                    copy[y * w + x] = false;
                    continue;
                }
    
                int free = 0;
                for(int dx = -1; dx <= 1; dx++) for(int dy = -1; dy <= 1; dy++) {
                    if(dy == 0 && dx == 0)continue;
                    if(free > 4)break;
                    int gx = x + dx;
                    int gy = y + dy;
                    if(gy < 0 || gy >= h || gx < 0 || gx >= w || data.field[gy * w + gx] == false) free++;
                }
    
                if(free > 4) {
                    removed++;
                    copy[y * w + x] = false;
                } else {
                    copy[y * w + x] = true;
                }
            }
        }
        
        // swap data.field with copy
        bool *tmp = data.field;
        data.field = copy;
        copy = tmp;

        count += removed;
    } while(removed > 0);

    free(copy);

    printf("Count: %d\n", count);
}



int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s inputfile.txt\n\n", argv[0]);
        return 1;
    }

    struct timespec start, end;

    timespec_get(&start, TIME_UTC);
    struct Field f = parse(argv[1]);
    timespec_get(&end, TIME_UTC);
    printf("Found a %d x %d field\n", f.w, f.h);
    print_time("Parsing", start, end);
    
    printf("Day 4 - Part 1: ");
    timespec_get(&start, TIME_UTC);
    part1(f);
    timespec_get(&end, TIME_UTC);
    print_time("Part 1", start, end);

    printf("Day 4 - Part 2: ");
    timespec_get(&start, TIME_UTC);
    part2(f);
    timespec_get(&end, TIME_UTC);
    print_time("Part 2", start, end);
    
    free(f.field);
    return 0;
}