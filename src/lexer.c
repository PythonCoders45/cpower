#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_PRINT,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
} Token;

// Simple lexer function to read .cp source code
Token next_token(const char** src) {
    Token token;
    while (**src == ' ' || **src == '\t' || **src == '\n') (*src)++; // Skip whitespace

    if (**src == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    if (**src == '=') {
        token.type = TOKEN_ASSIGN;
        strcpy(token.lexeme, "=");
        (*src)++;
        return token;
    }

    if (**src == ';') {
        token.type = TOKEN_SEMICOLON;
        strcpy(token.lexeme, ";");
        (*src)++;
        return token;
    }

    // Handle numbers
    if (**src >= '0' && **src <= '9') {
        int i = 0;
        while (**src >= '0' && **src <= '9') {
            token.lexeme[i++] = *(*src)++;
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    // Handle identifiers or keywords (e.g., int, print)
    if ((**src >= 'a' && **src <= 'z') || (**src >= 'A' && **src <= 'Z')) {
        int i = 0;
        while ((**src >= 'a' && **src <= 'z') || (**src >= 'A' && **src <= 'Z') || (**src >= '0' && **src <= '9')) {
            token.lexeme[i++] = *(*src)++;
        }
        token.lexeme[i] = '\0';

        if (strcmp(token.lexeme, "int") == 0) token.type = TOKEN_KEYWORD_INT;
        else if (strcmp(token.lexeme, "print") == 0) token.type = TOKEN_KEYWORD_PRINT;
        else token.type = TOKEN_IDENTIFIER;

        return token;
    }

    token.type = TOKEN_EOF;
    return token;
}s
