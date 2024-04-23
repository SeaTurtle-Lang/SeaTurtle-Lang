#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "../reader.c"
#include "../consts.h"
#include "../splits.h"

struct token lex(char* contents, int file_length, int offset) {
    char curr_token[MAX_TOKEN_LENGTH];
    int token_type = -1;

    char current = contents[offset];
    // char next_char = (offset == file_length-1) ? contents[offset+1] : "";

    while (isspace(current)) {
        current = contents[++offset];
    }

    if (isdigit(current)) {
        int length = 0;
        for (int i = offset; isdigit(contents[i]); i++) {
            curr_token[i-offset] = contents[i];
            length++;
        }
        return tk_init(INT_LIT, offset+length, curr_token);
    }

    switch (current) {
        case ';':
            return tk_valueless_init(ENDL, offset+1);
        case '+':
            return tk_valueless_init(ADD, offset+1);
        case '-':
            return tk_valueless_init(SUB, offset+1);
        case '*':
            return tk_valueless_init(MUL, offset+1);
        case '/':
            return tk_valueless_init(DIV, offset+1);
        case '=':
            char next_char = contents[offset+1];
            switch (next_char) {
                case '=':
                    return tk_valueless_init(EQ, offset+2);
                case '>':
                    return tk_valueless_init(ASSIGN, offset+2);
            }
        default:
            printf("unrecognized: %c!\n", current);
            return tk_valueless_init(UNK, offset+1);
    }

    struct token eof_token = tk_valueless_init(TK_EOF, -1);
    return eof_token;
}