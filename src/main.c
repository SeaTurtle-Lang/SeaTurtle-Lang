#include <stdio.h>
#include "splits.h"
#include "errors.c"
#include "syntax/lexer.c"

void run_checks(int argc, char** argv) {
    if (argc != 2) {
        file_not_specified_error(argc);
    }

    char* SRC_FILE = argv[1];

    struct bool_file src_file_exists = file_exists(SRC_FILE);
    if (src_file_exists.status_code == 1) {
        file_does_not_exist_error(SRC_FILE);
    }
}

int main(int argc, char** argv) {
    run_checks(argc, argv);

    FILE* fp = fopen(argv[1], "r");

    int file_length = get_file_length(fp);
    char contents[file_length];

    get_file_contents(fp, contents);

    printf("%s\n", contents);
    for (int i = 0; i < file_length; i++) {
        printf("%d", i);
    }
    printf("\n");

    int offset = 0;

    while (offset < file_length) {
        struct token tk = lex(contents, file_length, offset);
        offset = tk.offset;
        printf("token type = %d, offset = %d\n", tk.token, offset);
    }


    return 0;
}