#include <stdio.h>
#include <time.h>
typedef unsigned long long uint64;

void print_time(const char* name, struct timespec start, struct timespec end) {
    printf("\e[0;90m \300 %s took %.3lfms\e[0m\n", name, (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0);
}


// this should be faster than sscanf because it does less
// accepts a pointer to a pointer to a char, so I can change where the "file cursor points to"
// (i.e. I can read multiple digits)
uint64 parse_num(char **c) {
    uint64 num = 0;
    while(**c >= '0' && **c <= '9') {
        num *= 10;
        num += **c - '0';
        (*c)++;
    }

    return num;
}

// return a 0 terminated string from a file read in 1 go
char* read_all(const char* filename) {
    FILE* pInput = fopen(filename, "rb");
    if(pInput == NULL) {
        fprintf(stderr, "Invalid file: %s\n", filename);
        exit(1);
    }

    // get file size
    fseek(pInput, 0, SEEK_END); // seek to end of file
    long size  = ftell(pInput); // get current file pointer
    fseek(pInput, 0, SEEK_SET); // seek back to beginning of file

        
    char* buf = malloc(size + 1);
    if(buf == NULL) {
        fprintf(stderr, "Could not allocate memory to read file");
        exit(3);
    }
    
    fread(buf, 1, size, pInput);
    fclose(pInput);

    buf[size] = 0;
    
    return buf;
}