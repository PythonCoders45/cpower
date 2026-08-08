#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <memory>

// Forward declare tokens from lexer.c
extern "C" {
    #include "lexer.h"
}

// AST Node base structures
struct ASTNode {
    virtual ~ASTNode() = default;
};

struct VarDeclNode : public ASTNode {
    std::string type;
    std::string name;
    std::string value;
};

struct PrintNode : public ASTNode {
    std::string variableName;
};

struct BinaryExprNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

class CPowerParser {
private:
    const char* sourceCursor;
    int lineTracker;
    int colTracker;
    Token currentToken;

    void advanceToken();
    bool checkToken(TokenType type);
    void consume(TokenType type, const std::string& errorMessage);

public:
    CPowerParser(const char* source);
    std::vector<std::unique_ptr<ASTNode>> parseProgram();
};

#endif // PARSER_H
