#ifndef _LEXERH_
#define _LEXERH_

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
    TokenTypeRparen,
    TokenTypeLBrace,
    TokenTypeRBrace,
}TokenType;

typedef struct SToken{
    TokenType type;
    char* Literal;
};

#endif // !_LEXERH_
#define _LEXERH_