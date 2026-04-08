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

    size_t len = sizeof(expected) /sizeof(expected[0]);

    Lexer* l = New(input);
    assert(l != NULL);

    for(size_t i = 0; i < len; i++){
        Token* tok = nextToken(l);
        assert(tok != NULL);
        assert(tok->type = expected[i]);
        free(tok);
    }

    free(l); //Free lexer

    printf("Token passed the test \n");
}