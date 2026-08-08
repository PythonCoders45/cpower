#ifndef VM_H
#define VM_H

#include <vector>
#include <string>
#include <unordered_map>

enum OpCode {
    OP_CONSTANT,    // Push constant value onto stack
    OP_LOAD_VAR,    // Load variable value onto stack
    OP_STORE_VAR,   // Store stack value into a variable
    OP_ADD,         // Add top two stack elements
    OP_SUBTRACT,    // Subtract top two stack elements
    OP_PRINT,       // Print top of stack
    OP_HALT         // Stop execution
};

class VirtualMachine {
private:
    std::vector<int> stack;
    std::unordered_map<std::string, int> memory;

    void push(int value);
    int pop();

public:
    void execute(const std::vector<uint8_t>& bytecode, const std::vector<int>& constants);
};

#endif
