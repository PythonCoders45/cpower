#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "parser.hpp"
#include <unordered_map>
#include <string>

class Evaluator {
    // Stores variables in memory: map of variable name -> value
    std::unordered_map<std::string, std::string> variables;

public:
    void execute(const std::unique_ptr<ASTNode>& node);
};

#endif
