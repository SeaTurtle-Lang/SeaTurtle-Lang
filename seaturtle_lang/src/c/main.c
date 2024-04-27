#include <stdio.h>
#include "splits.h"
#include "errors.c"
#include "consts.h"
#include "lexer/lexer.c"

extern struct token* get_token_values(char* contents, struct token_idt tokens[], int len);

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
    struct token_idt* tokens;

    tokens = (struct token_idt*) malloc(STARTING_TOKEN_COUNT * sizeof(struct token_idt));

    while (offset < file_length) {
        struct token_idt tk = lex(contents, file_length, offset);
        tokens[token_count] = tk;

        offset = tk.offset;
        if (++token_count > STARTING_TOKEN_COUNT) {
            realloc(tokens, token_count * sizeof(struct token_idt));
        }        
    }

    struct token* new_tokens = get_token_values(contents, tokens, token_count);
    for (int i = 0; i < token_count; i++) {
        printf("%d '%s'\n", new_tokens[i].token, new_tokens[i].value);
    }

    return 0;
}