#ifndef _LEXERH_
#define _LEXERH_
#include <stddef.h>

typedef enum{
    TokenTypeIllegal,
    TokenTypeEOF,
    TokenTypeIdent,
    TokenTypeInt,
    TokenTypeAssign,
    TokenTypePlus,
    TokenTypeComma,
    TokenTypeSemicolon,
    TokenTypeLParen,
    TokenTypeRParen,
    TokenTypeLBrace,
    TokenTypeRBrace,
    TokenTypeLet,
    TokenTypeFunction,
} TokenType;

typedef struct SToken{
    TokenType type;
    char* literal;
}Token;

typedef struct SLexer Lexer;

Lexer* init_lexer(const char* input);
Token* create_token(Lexer *l);

#endif