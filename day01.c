#include <stdio.h>

void part1(const char* filename) {
    FILE *pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Error opening input file");
        return;
    }

    char dir = 0;
    int num = 0;
    int current = 50;
    int pass = 0;

    while(!feof(pInput) && fscanf(pInput, "%c%d\n", &dir, &num)) {
        if(dir == 'R') {
            current += num;
        } else if (dir == 'L') {
            current -= num;
        }

        if(current > 99) {
            current = current % 100;
        } else while (current < 0) {
            current += 100;
        }

        // printf("The dial is rotated %c%d to point at %d\n", dir, num, current);

        if(current == 0) {
            pass++;
        }
    }

    fclose(pInput);
    printf("Password is %d\n", pass);
}

void part2(const char* filename) {
    FILE *pInput = fopen(filename, "r");
    if(pInput == NULL) {
        fprintf(stderr, "Error opening input file");
        return;
    }

    char dir = 0;
    int num = 0;
    int current = 50;
    int pass = 0;

    while(!feof(pInput) && fscanf(pInput, "%c%d\n", &dir, &num)) {
        if(dir == 'R') {
            current += num;
            while(current > 99) {
                current -= 100;
                pass++;
            } 
        } else if (dir == 'L') {
            // we don't count "starting at 0" because we would have already counted that above or below
            if (current == 0) pass--;

            current -= num;
            while (current < 0) {
                current += 100;
                pass++;
            }

            // but if we end up again at 0 we count that.
            if (current == 0) pass++;
        }
    }

    fclose(pInput);
    printf("Password is %d\n", pass);
}


int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s inputfile.txt\n\n", argv[0]);
        return 1;
    }

    printf("Day 1 - part 1: ");
    part1(argv[1]);

    printf("Day 1 - part 2: ");
    part2(argv[1]);

    return 0;
}