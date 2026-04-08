#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lexer.h"

struct SLexer {
    const char* input; // Source code
    size_t input_len; 
    size_t position; // Current position in input
    size_t readPosition; // Next position to read
    char ch; // Current character
};

Token* newToken(TokenType token_type, char* literal);
void readChar(Lexer* l);
Token* nextToken(Lexer* l);

Lexer* New(const char* input){
    size_t len = sizeof(Lexer);
    Lexer* l = malloc(len);
    memset(l, 0, len);

    l->input = input;
    l->input_len = strlen(input);
    l->position = 0;
    l->readPosition = 0;
    l->ch = '\0';

    return l;
}

void readChar(Lexer* l){
    if(l->readPosition >= l->input_len){
        l->ch = '\0'; //EOF
    }else{
        l->ch = l->input[l->readPosition];
    }

    l->position = l->readPosition;
    l->readPosition++;
}

Token* nextToken(Lexer* l){
    // Skip whitespace first
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        readChar(l);
    }

    Token* tok = NULL;

    switch(l->ch){
        case '=' :
            tok = newToken(TokenTypeAssign, NULL);
            break;
        case ';' :
            tok = newToken(TokenTypeSemicolon, NULL);
            break;
        case '(' :
            tok = newToken(TokenTypeLParen, NULL);
            break;
        case ')' :
            tok = newToken(TokenTypeRParen, NULL);
            break;
        case ',' :
            tok = newToken(TokenTypeComma, NULL);
            break;
        case '+' :
            tok = newToken(TokenTypePlus, NULL);
            break;
        case '{' :
            tok = newToken(TokenTypeLBrace, NULL);
            break;
        case '}' :
            tok = newToken(TokenTypeRBrace, NULL);
            break;
        case '\0':  // EOF
            tok = newToken(TokenTypeEOF, "");
            break;
        default:
            tok = newToken(TokenTypeIllegal, "");
            break;
    }
    readChar(l);

    return tok;
}

Token* newToken(TokenType token_type, char* literal){
    size_t len = sizeof(Token);
    Token* tok = malloc(len);
    memset(tok, 0, len);

    tok->type = token_type;
    tok->literal = literal;

    return tok;
}