#include "lexer.h"
#include <string.h>
#include <ctype.h>

Token next_token(const char** src, int* line_tracker) {
    Token token;
    token.line = *line_tracker;

    while (**src == ' ' || **src == '\t' || **src == '\r') (*src)++;

    if (**src == '\n') {
        (*line_tracker)++;
        (*src)++;
        return next_token(src, line_tracker);
    }

    if (**src == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    if (**src == '=') { token.type = TOKEN_ASSIGN; strcpy(token.lexeme, "="); (*src)++; return token; }
    if (**src == '+') { token.type = TOKEN_PLUS; strcpy(token.lexeme, "+"); (*src)++; return token; }
    if (**src == '-') { token.type = TOKEN_MINUS; strcpy(token.lexeme, "-"); (*src)++; return token; }
    if (**src == ';') { token.type = TOKEN_SEMICOLON; strcpy(token.lexeme, ";"); (*src)++; return token; }
    if (**src == '{') { token.type = TOKEN_LBRACE; strcpy(token.lexeme, "{"); (*src)++; return token; }
    if (**src == '}') { token.type = TOKEN_RBRACE; strcpy(token.lexeme, "}"); (*src)++; return token; }
    if (**src == '(') { token.type = TOKEN_LPAREN; strcpy(token.lexeme, "("); (*src)++; return token; }
    if (**src == ')') { token.type = TOKEN_RPAREN; strcpy(token.lexeme, ")"); (*src)++; return token; }

    if (**src == '"') {
        (*src)++;
        int i = 0;
        while (**src != '"' && **src != '\0' && i < 127) {
            token.lexeme[i++] = *(*src)++;
        }
        token.lexeme[i] = '\0';
        if (**src == '"') (*src)++;
        token.type = TOKEN_LITERAL_STRING;
        return token;
    }

    if (isdigit(**src)) {
        int i = 0;
        while (isdigit(**src) && i < 127) {
            token.lexeme[i++] = *(*src)++;
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    if (isalpha(**src) || **src == '_') {
        int i = 0;
        while ((isalnum(**src) || **src == '_') && i < 127) {
            token.lexeme[i++] = *(*src)++;
        }
        token.lexeme[i] = '\0';

        if (strcmp(token.lexeme, "int") == 0) token.type = TOKEN_INT;
        else if (strcmp(token.lexeme, "string") == 0) token.type = TOKEN_STRING;
        else if (strcmp(token.lexeme, "void") == 0) token.type = TOKEN_VOID;
        else if (strcmp(token.lexeme, "print") == 0) token.type = TOKEN_PRINT;
        else if (strcmp(token.lexeme, "if") == 0) token.type = TOKEN_IF;
        else if (strcmp(token.lexeme, "while") == 0) token.type = TOKEN_WHILE;
        else if (strcmp(token.lexeme, "class") == 0) token.type = TOKEN_CLASS;
        else if (strcmp(token.lexeme, "return") == 0) token.type = TOKEN_RETURN;
        else token.type = TOKEN_IDENTIFIER;

        return token;
    }

    token.type = TOKEN_UNKNOWN;
    token.lexeme[0] = *(*src)++;
    token.lexeme[1] = '\0';
    return token;
}
