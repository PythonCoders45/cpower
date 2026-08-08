#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    KEYWORD_INT,
    KEYWORD_PRINT,
    IDENTIFIER,
    NUMBER,
    ASSIGN,
    PLUS,
    SEMICOLON,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string text;
};

#endif
