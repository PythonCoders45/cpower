#include "lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

static char peek(const char* src) {
    return *src;
}

static char advance(const char** src) {
    return *(*src)++;
}

static bool match(const char** src, char expected) {
    if (**src == '\0') return false;
    if (**src != expected) return false;
    (*src)++;
    return true;
}

// Skips whitespaces, tabs, carriage returns, newlines, and all forms of comments
static void skip_whitespace_and_comments(const char** src, int* line_tracker, int* col_tracker) {
    while (true) {
        char c = **src;
        if (c == ' ' || c == '\t' || c == '\r') {
            advance(src);
            (*col_tracker)++;
        } else if (c == '\n') {
            advance(src);
            (*line_tracker)++;
            *col_tracker = 1;
        } else if (c == '/' && *(*src + 1) == '/') {
            // Single-line comment: // ...
            while (**src != '\n' && **src != '\0') {
                advance(src);
            }
        } else if (c == '/' && *(*src + 1) == '*') {
            // Multi-line comment: /* ... */
            advance(src); advance(src);
            (*col_tracker) += 2;
            while (**src != '\0') {
                if (**src == '\n') {
                    (*line_tracker)++;
                    *col_tracker = 1;
                }
                if (**src == '*' && *(*src + 1) == '/') {
                    advance(src); advance(src);
                    (*col_tracker) += 2;
                    break;
                }
                advance(src);
                (*col_tracker)++;
            }
        } else {
            break;
        }
    }
}

Token next_token(const char** src, int* line_tracker, int* col_tracker) {
    Token token;
    skip_whitespace_and_comments(src, line_tracker, col_tracker);

    token.line = *line_tracker;
    token.col = *col_tracker;

    if (**src == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    char c = advance(src);
    (*col_tracker)++;

    // Comprehensive Operator and Punctuation Switch Board
    switch (c) {
        case '=':
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_EQUALS; strcpy(token.lexeme, "=="); return token; }
            if (match(src, '>')) { (*col_tracker)++; token.type = TOKEN_ARROW; strcpy(token.lexeme, "=>"); return token; }
            token.type = TOKEN_ASSIGN; strcpy(token.lexeme, "="); return token;
        case '+':
            if (match(src, '+')) { (*col_tracker)++; token.type = TOKEN_INCREMENT; strcpy(token.lexeme, "++"); return token; }
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_PLUS_ASSIGN; strcpy(token.lexeme, "+="); return token; }
            token.type = TOKEN_PLUS; strcpy(token.lexeme, "+"); return token;
        case '-':
            if (match(src, '-')) { (*col_tracker)++; token.type = TOKEN_DECREMENT; strcpy(token.lexeme, "--"); return token; }
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_MINUS_ASSIGN; strcpy(token.lexeme, "-="); return token; }
            token.type = TOKEN_MINUS; strcpy(token.lexeme, "-"); return token;
        case '*':
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_MUL_ASSIGN; strcpy(token.lexeme, "*="); return token; }
            token.type = TOKEN_MULTIPLY; strcpy(token.lexeme, "*"); return token;
        case '/':
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_DIV_ASSIGN; strcpy(token.lexeme, "/="); return token; }
            token.type = TOKEN_DIVIDE; strcpy(token.lexeme, "/"); return token;
        case '<':
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_LTE; strcpy(token.lexeme, "<="); return token; }
            token.type = TOKEN_LT; strcpy(token.lexeme, "<"); return token;
        case '>':
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_GTE; strcpy(token.lexeme, ">="); return token; }
            token.type = TOKEN_GT; strcpy(token.lexeme, ">"); return token;
        case '!':
            if (match(src, '=')) { (*col_tracker)++; token.type = TOKEN_NOT_EQUALS; strcpy(token.lexeme, "!="); return token; }
            token.type = TOKEN_NOT; strcpy(token.lexeme, "!"); return token;
        case '&':
            if (match(src, '&')) { (*col_tracker)++; token.type = TOKEN_LOGICAL_AND; strcpy(token.lexeme, "&&"); return token; }
            token.type = TOKEN_BITWISE_AND; strcpy(token.lexeme, "&"); return token;
        case '|':
            if (match(src, '|')) { (*col_tracker)++; token.type = TOKEN_LOGICAL_OR; strcpy(token.lexeme, "||"); return token; }
            token.type = TOKEN_BITWISE_OR; strcpy(token.lexeme, "|"); return token;
        case ';': token.type = TOKEN_SEMICOLON; strcpy(token.lexeme, ";"); return token;
        case ':': token.type = TOKEN_COLON; strcpy(token.lexeme, ":"); return token;
        case ',': token.type = TOKEN_COMMA; strcpy(token.lexeme, ","); return token;
        case '.': token.type = TOKEN_DOT; strcpy(token.lexeme, "."); return token;
        case '{': token.type = TOKEN_LBRACE; strcpy(token.lexeme, "{"); return token;
        case '}': token.type = TOKEN_RBRACE; strcpy(token.lexeme, "}"); return token;
        case '(': token.type = TOKEN_LPAREN; strcpy(token.lexeme, "("); return token;
        case ')': token.type = TOKEN_RPAREN; strcpy(token.lexeme, ")"); return token;
        case '[': token.type = TOKEN_LBRACKET; strcpy(token.lexeme, "["); return token;
        case ']': token.type = TOKEN_RBRACKET; strcpy(token.lexeme, "]"); return token;
    }

    // Full String Literal Parsing with Escape Sequencing (\n, \t, \r, \", \\)
    if (c == '"') {
        int i = 0;
        token.lexeme[i++] = '"';
        while (**src != '"' && **src != '\0' && i < 125) {
            char current = advance(src);
            (*col_tracker)++;
            if (current == '\\' && **src != '\0') {
                char escape_char = advance(src);
                (*col_tracker)++;
                if (escape_char == 'n') token.lexeme[i++] = '\n';
                else if (escape_char == 't') token.lexeme[i++] = '\t';
                else if (escape_char == 'r') token.lexeme[i++] = '\r';
                else if (escape_char == '"') token.lexeme[i++] = '"';
                else if (escape_char == '\\') token.lexeme[i++] = '\\';
                else {
                    token.lexeme[i++] = '\\';
                    token.lexeme[i++] = escape_char;
                }
            } else {
                token.lexeme[i++] = current;
            }
        }
        if (**src == '"') {
            advance(src);
            (*col_tracker)++;
            token.lexeme[i++] = '"';
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_LITERAL_STRING;
        return token;
    }

    // Number Literal Processing (Integers and Floating-Point numbers)
    if (isdigit(c)) {
        int i = 0;
        token.lexeme[i++] = c;
        while (isdigit(**src) && i < 125) {
            token.lexeme[i++] = advance(src);
            (*col_tracker)++;
        }
        if (**src == '.' && isdigit(*(*src + 1))) {
            token.lexeme[i++] = advance(src);
            (*col_tracker)++;
            while (isdigit(**src) && i < 125) {
                token.lexeme[i++] = advance(src);
                (*col_tracker)++;
            }
            token.type = TOKEN_FLOAT;
        } else {
            token.type = TOKEN_NUMBER;
        }
        token.lexeme[i] = '\0';
        return token;
    }

    // Identifiers and Exhaustive Keyword Dictionary Check
    if (isalpha(c) || c == '_') {
        int i = 0;
        token.lexeme[i++] = c;
        while ((isalnum(**src) || **src == '_') && i < 125) {
            token.lexeme[i++] = advance(src);
            (*col_tracker)++;
        }
        token.lexeme[i] = '\0';

        // Complete keyword dictionary mapped to C# and Java semantics
        if (strcmp(token.lexeme, "int") == 0) token.type = TOKEN_INT;
        else if (strcmp(token.lexeme, "string") == 0) token.type = TOKEN_STRING;
        else if (strcmp(token.lexeme, "bool") == 0) token.type = TOKEN_BOOL;
        else if (strcmp(token.lexeme, "void") == 0) token.type = TOKEN_VOID;
        else if (strcmp(token.lexeme, "print") == 0) token.type = TOKEN_PRINT;
        else if (strcmp(token.lexeme, "if") == 0) token.type = TOKEN_IF;
        else if (strcmp(token.lexeme, "else") == 0) token.type = TOKEN_ELSE;
        else if (strcmp(token.lexeme, "while") == 0) token.type = TOKEN_WHILE;
        else if (strcmp(token.lexeme, "for") == 0) token.type = TOKEN_FOR;
        else if (strcmp(token.lexeme, "break") == 0) token.type = TOKEN_BREAK;
        else if (strcmp(token.lexeme, "continue") == 0) token.type = TOKEN_CONTINUE;
        else if (strcmp(token.lexeme, "class") == 0) token.type = TOKEN_CLASS;
        else if (strcmp(token.lexeme, "enum") == 0) token.type = TOKEN_ENUM;
        else if (strcmp(token.lexeme, "List") == 0) token.type = TOKEN_LIST;
        else if (strcmp(token.lexeme, "Dictionary") == 0) token.type = TOKEN_DICTIONARY;
        else if (strcmp(token.lexeme, "public") == 0) token.type = TOKEN_PUBLIC;
        else if (strcmp(token.lexeme, "private") == 0) token.type = TOKEN_PRIVATE;
        else if (strcmp(token.lexeme, "return") == 0) token.type = TOKEN_RETURN;
        else token.type = TOKEN_IDENTIFIER;

        return token;
    }

    token.type = TOKEN_UNKNOWN;
    token.lexeme[0] = c;
    token.lexeme[1] = '\0';
    return token;
}
