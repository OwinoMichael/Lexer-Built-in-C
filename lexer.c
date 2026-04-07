#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lexer.h"

typedef struct SLexer{
    const char* input; // Source code
    size_t input_len; 
    size_t position; // Current position in input
    size_t readPosition; // Next position to read
    char ch; // Current character
} Lexer;

Lexer* New(const char* input){
    size_t len = sizeof(input);
    Lexer* l = malloc(len);
    memset(l, 0, len);

    l->input = input;
    l->input_len = len;
    l->position = 0;
    l->readPosition = 0;
    l->ch = NULL;

    return l;
}

void readChar(Lexer* l){
    if(l->readPosition >= l->input_len){
        l->ch = '\0';
    }else{
        l->ch = l->input[l->readPosition];
    }

    l->position = l->readPosition;
    l->readPosition++;
}