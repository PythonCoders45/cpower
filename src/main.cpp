#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/token.h"
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "evaluator.hpp"

// Helper function to read a .cp source file entirely into a string buffer
std::string readSourceFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open source file '" << filepath << "'" << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    // Check if the user provided a script path argument
    if (argc < 2) {
        std::cout << "Usage: c_power <source_file.cp>\n";
        return 1;
    }

    std::string filepath = argv[1];
    std::string sourceCode = readSourceFile(filepath);
    
    if (sourceCode.empty()) {
        return 1;
    }

    // 1. Lexer: Convert raw text into tokens
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.tokenize();

    // 2. Parser: Convert tokens into an Abstract Syntax Tree (AST)
    Parser parser(tokens);

    // 3. Evaluator: Execute the AST nodes and run the program
    Evaluator evaluator;

    while (auto stmt = parser.parseStatement()) {
        evaluator.execute(stmt);
    }

    return 0;
}
