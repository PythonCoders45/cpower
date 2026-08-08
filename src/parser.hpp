#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "token.hpp" // Assuming you have a Token struct/class
#include <string>
#include <vector>
#include <memory>

enum class ASTNodeType {
    VAR_DECL,
    PRINT_STMT
};

// AST Node Structure
struct ASTNode {
    ASTNodeType type;
    std::string name;
    std::string value;
};

class Parser {
    std::vector<Token> tokens;
    size_t current = 0;

    Token peek();
    Token advance();
    bool check(TokenType type);
    Token consume(TokenType type, const std::string& errorMessage);

public:
    Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parseStatement();
};

#endif
