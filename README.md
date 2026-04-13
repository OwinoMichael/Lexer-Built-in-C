# Sam Language Lexer in C

A lexical analyzer (lexer/tokenizer) implementation in C for the Sam programming language, based on the "Writing An Interpreter In Go" book by Thorsten Ball.

## Overview

This lexer breaks down Sam language source code into tokens, which is the first step in building an interpreter. It recognizes keywords, identifiers, numbers, and various operators/delimiters.

## Features

- **Token Recognition**: Identifies 14 different token types
- **Keyword Detection**: Recognizes `let` and `fn` keywords
- **Identifier Support**: Handles variable and function names (alphanumeric + underscore)
- **Number Parsing**: Tokenizes integer literals
- **Operator & Delimiter Support**: Handles `=`, `+`, `()`, `{}`, `,`, `;`
- **Whitespace Handling**: Automatically skips whitespace, tabs, and newlines
- **Memory Safe**: Proper memory allocation and deallocation

## Project Structure

```
.
├── lexer.h           # Header file with type definitions and API
├── lexer.c           # Lexer implementation
└── main.c            # Test suite with example usage
```

## Token Types

| Token Type | Description | Example |
|------------|-------------|---------|
| `TokenTypeIdent` | Identifier | `x`, `foo`, `my_var` |
| `TokenTypeInt` | Integer literal | `5`, `10`, `42` |
| `TokenTypeLet` | `let` keyword | `let` |
| `TokenTypeFunction` | `fn` keyword | `fn` |
| `TokenTypeAssign` | Assignment operator | `=` |
| `TokenTypePlus` | Addition operator | `+` |
| `TokenTypeComma` | Comma separator | `,` |
| `TokenTypeSemicolon` | Semicolon | `;` |
| `TokenTypeLParen` | Left parenthesis | `(` |
| `TokenTypeRParen` | Right parenthesis | `)` |
| `TokenTypeLBrace` | Left brace | `{` |
| `TokenTypeRBrace` | Right brace | `}` |
| `TokenTypeEOF` | End of file | - |
| `TokenTypeIllegal` | Unrecognized token | - |

## Building

### Prerequisites
- GCC or Clang compiler
- Make (optional)

### Compilation

```bash
# Using GCC
gcc -o lexer main.c lexer.c -std=c11 -Wall -Wextra

# Using Clang
clang -o lexer main.c lexer.c -std=c11 -Wall -Wextra
```

### Running Tests

```bash
./lexer
```

Expected output:
```
Token 1 passed the test
Token 2 passed the test
```

## Usage

### Basic Example

```c
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* input = "let x = 5;";
    
    Lexer* lexer = init_lexer(input);
    
    Token* tok;
    while ((tok = create_token(lexer))->type != TokenTypeEOF) {
        printf("Type: %d, Literal: %s\n", tok->type, tok->literal);
        
        if (tok->literal) {
            free(tok->literal);
        }
        free(tok);
    }
    
    free(tok);  // Free EOF token
    free(lexer);
    
    return 0;
}
```

### Example Input/Output

**Input:**
```
let add = fn(x, y) { x + y };
```

**Tokens Generated:**
```
TokenTypeLet       -> "let"
TokenTypeIdent     -> "add"
TokenTypeAssign    -> "="
TokenTypeFunction  -> "fn"
TokenTypeLParen    -> "("
TokenTypeIdent     -> "x"
TokenTypeComma     -> ","
TokenTypeIdent     -> "y"
TokenTypeRParen    -> ")"
TokenTypeLBrace    -> "{"
TokenTypeIdent     -> "x"
TokenTypePlus      -> "+"
TokenTypeIdent     -> "y"
TokenTypeRBrace    -> "}"
TokenTypeSemicolon -> ";"
TokenTypeEOF       -> ""
```

## API Reference

### `Lexer* init_lexer(const char* input)`
Initializes a new lexer with the given input string.

**Parameters:**
- `input`: Source code string to tokenize

**Returns:**
- Pointer to initialized `Lexer` structure

**Example:**
```c
Lexer* lexer = init_lexer("let x = 5;");
```

### `Token* create_token(Lexer* l)`
Generates the next token from the input.

**Parameters:**
- `l`: Pointer to initialized lexer

**Returns:**
- Pointer to newly created `Token` structure

**Note:** Caller is responsible for freeing the token and its literal (if not NULL).

**Example:**
```c
Token* tok = create_token(lexer);
if (tok->literal) {
    free(tok->literal);
}
free(tok);
```

## Memory Management

The lexer allocates memory dynamically. Ensure proper cleanup:

```c
Token* tok = create_token(lexer);

// Use token...

// Free token literal if it exists
if (tok->literal) {
    free(tok->literal);
}

// Free token
free(tok);

// Free lexer when done
free(lexer);
```

## Testing

The included test suite (`main.c`) verifies:
1. Individual operator/delimiter recognition
2. Complex statement parsing with keywords, identifiers, and numbers

Run tests with:
```bash
./lexer
```

All tests use assertions to verify correct token types are generated.

## Limitations

Current limitations:
- Only recognizes integers (no floats)
- Limited keyword set (`let`, `fn` only)
- No string literal support
- No comment handling
- Basic operator set (only `=` and `+`)

## Future Enhancements

Potential additions:
- [ ] More operators (`-`, `*`, `/`, `==`, `!=`, `<`, `>`)
- [ ] String literal support
- [ ] Boolean keywords (`true`, `false`)
- [ ] Control flow keywords (`if`, `else`, `return`)
- [ ] Comment support (`//` and `/* */`)
- [ ] Floating-point numbers
- [ ] Better error reporting with line/column numbers

## References

This implementation is based on:
- **Book**: "Writing An Interpreter In Go" by Thorsten Ball
- **Language**: Sam programming language

## License

This is an educational project. Feel free to use and modify as needed.

## Contributing

This is a learning project, but suggestions and improvements are welcome!

---

**Author:** Educational implementation  
**Language:** C11  
**Status:** Working lexer implementation
