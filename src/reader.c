#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "splits.h"
#include "consts.h"

struct bool_file file_exists(char file_path[]) {
    FILE* fptr;
    struct bool_file file_not_exists = { 1, NULL };

    fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        return file_not_exists;
    }
    struct bool_file file_found = { 0, fptr };
    return file_found;
}

int get_file_length(FILE* fp) {
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);

    return size;
}

char *get_file_contents(FILE* fp, char* text) {
    int file_size = get_file_length(fp);

    fread(text, file_size, 1, fp);
    text[file_size] = 0;

    return text;
}
