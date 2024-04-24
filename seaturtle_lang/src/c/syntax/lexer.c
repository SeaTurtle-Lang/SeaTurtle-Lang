#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "../reader.c"
#include "../consts.h"
#include "../splits.h"

struct token lex(char* contents, int file_length, int offset) {
    int token_type = -1;
    int length = 0;

    char current = contents[offset];

    while (isspace(current)) {
        current = contents[++offset];
    }

    if (isdigit(current)) {
        int length = 0;
        for (int i = offset; isdigit(contents[i]); i++) {
            length++;
        }

        return tk_init(INT_LIT, offset+length);
    }

    switch (current) {
        case ';': return tk_init(ENDL, offset+2);
        case '+': return tk_init(ADD, offset+1);
        case '-': return tk_init(SUB, offset+1);
        case '*': return tk_init(MUL, offset+1);
        case '/': return tk_init(DIV, offset+1);
        case '=':
            char next_char = contents[offset+1];
            switch (next_char) {
                case '=':
                    return tk_init(EQ, offset+2);
                case '>':
                    return tk_init(ASSIGN, offset+2);
            }
        case '"':
            for (int i = offset+1; contents[i] != '"'; i++) {
                length++;
            }
            return tk_init(STRING, offset+length+2);
        case '\'':
            for (int i = offset+1; contents[i] != '\''; i++) {
                length++;
            }
            return tk_init(STRING, offset+length+2);
        default:
            if isalpha(current) {
                int length = 0;
                for (int i = offset; isalpha(contents[i]); i++) {
                    length++;
                }
                return tk_init(LABEL, offset+length);
            }

            printf("unrecognized: %c!\n", current);
            return tk_init(UNK, offset+1);
    }

    struct token eof_token = tk_init(TK_EOF, -1);
    return eof_token;
}