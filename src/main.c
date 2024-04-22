#include <stdio.h>
#include "reader.c"
#include "errors.c"

int main(int argc, char** argv) {
    if (argc != 2) {
        file_not_specified_error(argc);
    }

    char* SRC_FILE = argv[1];

    bool src_file_exists = file_exists(SRC_FILE);
    if (src_file_exists == 1) {
        file_does_not_exist_error(SRC_FILE);
    }

    printf("%s\n", get_file_contents(SRC_FILE));
    return 0;
}