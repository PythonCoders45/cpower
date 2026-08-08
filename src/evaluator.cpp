#include "evaluator.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>

// Helper to convert a runtime value back into a printable string
std::string Evaluator::valueToString(const RuntimeValue& val) {
    if (std::holds_alternative<int>(val)) {
        return std::to_string(std::get<int>(val));
    } else if (std::holds_alternative<double>(val)) {
        return std::to_string(std::get<double>(val));
    } else {
        std::string s = std::get<std::string>(val);
        // Strip outer quotes if it's a string literal
        if (s.length() >= 2 && s.front() == '"' && s.back() == '"') {
            return s.substr(1, s.length() - 2);
        }
        return s;
    }
}

// Evaluates expressions (handles variables, literals, and basic math)
RuntimeValue Evaluator::evaluateExpression(const std::string& expr) {
    // 1. Check if it's a string literal (e.g. "Hello")
    if (expr.length() >= 2 && expr.front() == '"' && expr.back() == '"') {
        return expr;
    }

    // 2. Check if it's an existing variable in memory
    if (variables.find(expr) != variables.end()) {
        return variables[expr];
    }

    // 3. Check if it's a floating-point number
    if (expr.find('.') != std::string::npos) {
        try {
            return std::stod(expr);
        } catch (...) {}
    }

    // 4. Check if it's an integer number
    try {
        return std::stoi(expr);
    } catch (...) {}

    // Fallback as raw string
    return expr;
}

// Executes AST Nodes
void Evaluator::execute(const std::unique_ptr<ASTNode>& node) {
    if (!node) return;

    if (node->type == ASTNodeType::VAR_DECL) {
        // Evaluate the right-hand side value and store it in memory under node->name
        RuntimeValue val = evaluateExpression(node->value);
        variables[node->name] = val;
    } 
    else if (node->type == ASTNodeType::PRINT_STMT) {
        // Evaluate the target expression and print the output
        RuntimeValue val = evaluateExpression(node->name);
        std::cout << valueToString(val) << std::endl;
    }
}
