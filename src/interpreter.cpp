#include "token.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class Interpreter {
    std::vector<Token> tokens;
    size_t index = 0;
    std::unordered_map<std::string, int> variables;

    Token peek() { return tokens[index]; }
    Token consume() { return tokens[index++]; }

public:
    Interpreter(const std::vector<Token>& t) : tokens(t) {}

    void interpret() {
        while (peek().type != TokenType::END_OF_FILE) {
            
            // Handle variable declarations/assignments: int x = 5;
            if (peek().type == TokenType::KEYWORD_INT) {
                consume(); // skip 'int'
                std::string varName = consume().text; // get variable name
                consume(); // skip '='
                int value = std::stoi(consume().text); // get number
                consume(); // skip ';'
                
                variables[varName] = value;
            }
            // Handle print commands: print x; or print 10;
            else if (peek().type == TokenType::KEYWORD_PRINT) {
                consume(); // skip 'print'
                std::string target = consume().text;
                consume(); // skip ';'

                if (variables.find(target) != variables.end()) {
                    std::cout << variables[target] << std::endl;
                } else {
                    std::cout << target << std::endl; // print literal if not variable
                }
            } else {
                index++;
            }
        }
    }
};
