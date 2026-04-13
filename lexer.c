#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"

struct SLexer {
    const char* input;
    size_t input_len;
    size_t position;
    size_t readPosition;
    char ch;
};

static void read_char(Lexer* l);
static void skip_whitespace(Lexer* l);
static const char* read_ident(Lexer* l, size_t* len);
static const char* read_num(Lexer* l, size_t* len);
static int is_letter(char c);
static int is_digit(char c);
static TokenType lookup_ident(const char* ident, size_t len);

Lexer* init_lexer(const char* input){
    size_t len = sizeof(Lexer);
    Lexer* l = malloc(len);
    memset(l, 0, len);

    l->input = input;
    l->input_len = strlen(input);
    l->position = 0;
    l->readPosition = 0;
    l->ch = '\0';

    read_char(l);

    return l;
}

Token* init_token(TokenType token_type, char* literal){
    size_t len = sizeof(Token);
    Token* tok = malloc(len);
    memset(tok, 0, len);

    tok->type = token_type;
    tok->literal = literal;

    return tok;
}

Token* create_token(Lexer* l) {
    skip_whitespace(l);

    Token* tok = NULL;

    if (is_letter(l->ch)) {
        size_t len = 0;
        const char* ident = read_ident(l, &len);
        TokenType type = lookup_ident(ident, len);
        
        char* literal = NULL;
        if (type == TokenTypeIdent) {
            literal = strndup(ident, len);
        }
        
        tok = init_token(type, literal);
        return tok;
    }
    
    if (is_digit(l->ch)) {
        size_t len = 0;
        const char* digit = read_num(l, &len);
        char* literal = strndup(digit, len);
        
        tok = init_token(TokenTypeInt, literal);
        return tok;
    }

    switch (l->ch) {
        case '=':
            tok = init_token(TokenTypeAssign, NULL);
            break;
        case ';':
            tok = init_token(TokenTypeSemicolon, NULL);
            break;
        case '(':
            tok = init_token(TokenTypeLParen, NULL);
            break;
        case ')':
            tok = init_token(TokenTypeRParen, NULL);
            break;
        case ',':
            tok = init_token(TokenTypeComma, NULL);
            break;
        case '+':
            tok = init_token(TokenTypePlus, NULL);
            break;
        case '{':
            tok = init_token(TokenTypeLBrace, NULL);
            break;
        case '}':
            tok = init_token(TokenTypeRBrace, NULL);
            break;
        case '\0':
            tok = init_token(TokenTypeEOF, "");
            break;
        default:
            tok = init_token(TokenTypeIllegal, "");
            break;
    }
    
    read_char(l);
    return tok;
}

static void read_char(Lexer* l){
    if(l->readPosition >= l->input_len){
        l->ch = '\0';
    }else{
        l->ch = l->input[l->readPosition];
    }

    l->position = l->readPosition;
    l->readPosition++;
}

static void skip_whitespace(Lexer* l) {
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        read_char(l);
    }
}

static const char* read_ident(Lexer* l, size_t* len) {
    size_t start_pos = l->position;

    while (is_letter(l->ch)) {
        read_char(l);
    }

    if (len) {
        *len = l->position - start_pos;
    }

    return l->input + start_pos;
}

static const char* read_num(Lexer* l, size_t* len) {
    size_t start_pos = l->position;

    while (is_digit(l->ch)) {
        read_char(l);
    }

    if (len) {
        *len = l->position - start_pos;
    }

    return l->input + start_pos;
}

static int is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static TokenType lookup_ident(const char* ident, size_t len) {
    if (len == 3 && strncmp(ident, "let", 3) == 0) {
        return TokenTypeLet;
    }
    if (len == 2 && strncmp(ident, "fn", 2) == 0) {
        return TokenTypeFunction;
    }
    return TokenTypeIdent;
}