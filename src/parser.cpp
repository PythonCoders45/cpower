#include "parser.h"
#include "error.h"
#include <iostream>
#include <cstdlib>

CPowerParser::CPowerParser(const char* source) {
    sourceCursor = source;
    lineTracker = 1;
    colTracker = 1;
    currentToken = next_token(&sourceCursor, &lineTracker, &colTracker);
}

void CPowerParser::advanceToken() {
    currentToken = next_token(&sourceCursor, &lineTracker, &colTracker);
}

bool CPowerParser::checkToken(TokenType type) {
    return currentToken.type == type;
}

void CPowerParser::consume(TokenType type, const std::string& errorMessage) {
    if (currentToken.type == type) {
        advanceToken();
    } else {
        report_error(ERROR_SYNTAX, currentToken.line, errorMessage);
    }
}

std::vector<std::unique_ptr<ASTNode>> CPowerParser::parseProgram() {
    std::vector<std::unique_ptr<ASTNode>> statements;

    while (currentToken.type != TOKEN_EOF) {
        // Parse Variable Declarations: e.g., int score = 42;
        if (checkToken(TOKEN_INT) || checkToken(TOKEN_STRING) || checkToken(TOKEN_BOOL)) {
            auto node = std::make_unique<VarDeclNode>();
            
            node->type = currentToken.lexeme;
            advanceToken();

            if (currentToken.type == TOKEN_IDENTIFIER) {
                node->name = currentToken.lexeme;
                advanceToken();
            } else {
                report_error(ERROR_SYNTAX, currentToken.line, "Expected variable name identifier.");
            }

            consume(TOKEN_ASSIGN, "Expected '=' in variable initialization.");

            if (currentToken.type == TOKEN_NUMBER || currentToken.type == TOKEN_LITERAL_STRING) {
                node->value = currentToken.lexeme;
                advanceToken();
            } else {
                report_error(ERROR_SYNTAX, currentToken.line, "Expected literal value assignment.");
            }

            consume(TOKEN_SEMICOLON, "Expected ';' at the end of statement.");
            statements.push_back(std::move(node));
        }
        // Parse Print Statements: e.g., print score;
        else if (checkToken(TOKEN_PRINT)) {
            auto node = std::make_unique<PrintNode>();
            advanceToken();

            if (currentToken.type == TOKEN_IDENTIFIER) {
                node->variableName = currentToken.lexeme;
                advanceToken();
            } else {
                report_error(ERROR_SYNTAX, currentToken.line, "Expected variable name after print.");
            }

            consume(TOKEN_SEMICOLON, "Expected ';' after print statement.");
            statements.push_back(std::move(node));
        } else {
            report_error(ERROR_SYNTAX, currentToken.line, std::string("Unexpected token: ") + currentToken.lexeme);
            advanceToken(); // Recover by skipping
        }
    }

    return statements;
}
