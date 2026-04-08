#ifndef _LEXERH_
#define _LEXERH_
#include <stddef.h>

typedef struct SLexer Lexer;

Lexer* New(const char* input);

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
} TokenType;

typedef struct SToken{
    TokenType type;
    char* literal;
}Token;

// Function declarations
Token* newToken(TokenType token_type, char* literal);
void readChar(Lexer* l);
Token* nextToken(Lexer* l);


#endif // !_LEXERH_
