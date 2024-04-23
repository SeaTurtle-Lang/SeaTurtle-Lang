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

struct token {
    int token;
    int offset;
    char* value;
};

struct token tk_valueless_init(int token, int offset) {
    struct token result;
    result.token = token;
    result.offset = offset;
    result.value = "";
    return result;
}

struct token tk_init(int token, int offset, char* value) {
    struct token result;
    result.token = token;
    result.offset = offset;
    result.value = value;
    return result;
}

#endif