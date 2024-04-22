#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SRC_FILE "examples/main.st"

bool file_exists(char file_path[]) {
    FILE* fptr;

    fptr = fopen(file_path, "r");
    
    return (fptr != NULL);
}

int main() {
    bool src_file_exists = file_exists(SRC_FILE);

    printf("%d\n", src_file_exists);
    return 0;
}