#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool file_exists(char file_path[]) {
    FILE* fptr;

    fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        return 1;
    }
    if (fclose(fptr) == EOF) {
        return 1;
    }
    return 0;
}

char *get_file_contents(char file_path[]) {
    char *text = "Hello, World";
    return text;
}
