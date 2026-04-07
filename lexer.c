#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lexer.h"

typedef struct SLexer{
    const char * input; //line of code
    size_t input_len; //
    size_t position;
    size_t readPosition;
    char ch;
} Token;