#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_INT, TOKEN_STRING, TOKEN_VOID, TOKEN_PRINT,
    TOKEN_IF, TOKEN_WHILE, TOKEN_CLASS, TOKEN_RETURN,
    TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_LITERAL_STRING,
    TOKEN_ASSIGN, TOKEN_PLUS, TOKEN_MINUS, TOKEN_SEMICOLON,
    TOKEN_LBRACE, TOKEN_RBRACE, TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_EOF, TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[128];
    int line;
} Token;

Token next_token(const char** src, int* line_tracker);

#endif
