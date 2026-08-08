#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "parser.hpp"
#include <unordered_map>
#include <string>
#include <variant>

// A runtime value type that can hold numbers or strings
using RuntimeValue = std::variant<int, double, std::string>;

class Evaluator {
    // Memory map storing variable name -> value
    std::unordered_map<std::string, RuntimeValue> variables;

    RuntimeValue evaluateExpression(const std::string& expr);
    std::string valueToString(const RuntimeValue& val);

public:
    void execute(const std::unique_ptr<ASTNode>& node);
};

#endif
