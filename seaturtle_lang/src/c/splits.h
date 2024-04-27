#include <stdbool.h>
#include <stdio.h>

#ifndef BOOL_FILE
#define BOOL_FILE

struct bool_file {
    bool status_code;
    FILE* fp;
};

#endif

#ifndef TOKEN
#define TOKEN

struct token_idt {
    int token;
    int offset;
};

struct token {
    int token;
    char* value;
};

struct token_idt tk_init(int token, int offset) {
    struct token_idt result;
    result.token = token;
    result.offset = offset;
    // result.value = "";
    return result;
}

#endif