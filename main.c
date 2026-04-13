#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include "lexer.h"

int main(){

    const char* input = "=+(),;{}";

    TokenType expected[] = {
        TokenTypeAssign,
        TokenTypePlus,
        TokenTypeLParen,
        TokenTypeRParen,
        TokenTypeComma,
        TokenTypeSemicolon,
        TokenTypeLBrace,   // Added
        TokenTypeRBrace    // Added
    };

    // let five = 5;
    // let ten = 10;
    // let add = fn(x,y){ x + y }
    // let result = add(five,ten);
    
    const char* input2 = "let five = 5; let ten = 10; let add = fn(x, y){x + y}; let result = add(five, ten)";

    TokenType expected2[] = {
        TokenTypeLet,      // "let"
        TokenTypeIdent,    // "five"
        TokenTypeAssign,   // "="
        TokenTypeInt,      // "5"
        TokenTypeSemicolon,// ";"
        TokenTypeLet,      // "let"
        TokenTypeIdent,    // "ten"
        TokenTypeAssign,   // "="
        TokenTypeInt,      // "10"
        TokenTypeSemicolon,// ";"
        TokenTypeLet,      // "let"
        TokenTypeIdent,    // "add"
        TokenTypeAssign,   // "="
        TokenTypeFunction, // "fn"
        TokenTypeLParen,   // "("
        TokenTypeIdent,    // "x"
        TokenTypeComma,    // ","
        TokenTypeIdent,    // "y"
        TokenTypeRParen,   // ")"
        TokenTypeLBrace,   // "{"
        TokenTypeIdent,    // "x"
        TokenTypePlus,     // "+"
        TokenTypeIdent,    // "y"
        TokenTypeRBrace,   // "}"
        TokenTypeSemicolon,// ";"
        TokenTypeLet,      // "let"
        TokenTypeIdent,    // "result"
        TokenTypeAssign,   // "="
        TokenTypeIdent,    // "add"
        TokenTypeLParen,   // "("
        TokenTypeIdent,    // "five"
        TokenTypeComma,    // ","
        TokenTypeIdent,    // "ten"
        TokenTypeRParen,
    };
    
    size_t len = sizeof(expected) /sizeof(expected[0]);
    size_t len2 = sizeof(expected2) /sizeof(expected2[0]);
    
    Lexer* l = init_lexer(input);
    assert(l != NULL);

    
    for(size_t i = 0; i < len; i++){
        Token* tok = create_token(l);
        assert(tok != NULL);
        assert(tok->type = expected[i]);
        free(tok);
    }

    printf("Token 1 passed the test \n");
    
    Lexer* l2 = init_lexer(input2);
    assert(l2 != NULL);

    for(size_t i = 0; i < len2; i++){
        Token* tok2 = create_token(l2);
        assert(tok2 != NULL);
        assert(tok2->type = expected2[i]);
        free(tok2);
    }

    free(l); //Free lexer

    printf("Token 2 passed the test \n");
}