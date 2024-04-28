#include <stdlib.h>

void file_not_specified_error(int argc) {
    printf("Fatal error: no file specified\n\tExpected argument count: 2\n\tGot argument count: %d\n", argc);
    exit(1);
}

void file_does_not_exist_error(char fp[]) {
    printf("Specified path does not exist\n\tGiven path: %s\n", fp);
    exit(1);
}

void reallocation_error() {
    printf("Encountered error trying to realloc");
    exit(1);
}