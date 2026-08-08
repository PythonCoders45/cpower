#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <string>
#include <vector>

class Lexer {
    std::string src;
    size_t pos = 0;
    int line = 1;
    int col = 1;

    char peek();
    char advance();
    bool match(char expected);
    void skipWhitespaceAndComments();

public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();
};

#endif // LEXER_HPP
