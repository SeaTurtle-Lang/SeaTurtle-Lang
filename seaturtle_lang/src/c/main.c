#include <stdio.h>
#include "splits.h"
#include "errors.c"
#include "syntax/lexer.c"

extern void parse(char* contents, struct token tokens[], int len);
// extern void hello_from_rust();

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
    // ========== INITIALIZATION ==========
    run_checks(argc, argv);

    FILE* fp = fopen(argv[1], "r");

    int file_length = get_file_length(fp);
    char contents[file_length];

    get_file_contents(fp, contents);

    // ======== END INITIALIZATION ========

    int offset = 0;

    int token_count = 0;

    while (offset < file_length) {
        struct token tk = lex(contents, file_length, offset);
        offset = tk.offset;
        token_count++;
    }

    struct token tokens[token_count];

    int curr_offset = 0;

    for (int i = 0; i < token_count; i++) {
        tokens[i] = lex(contents, file_length, curr_offset);
        struct token curr_token = tokens[i];
        printf("Token Type: %d, Offset: %d, Value: ", curr_token.token, curr_token.offset);
        for (int j = curr_offset; j < curr_token.offset; j++) {
            printf("%c", contents[j]);
        }
        printf("\n");
        curr_offset = curr_token.offset;
    }

    parse(contents, tokens, token_count);
    // hello_from_rust();

    return 0;
}