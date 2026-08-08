#ifndef VM_H
#define VM_H

#include <vector>
#include <string>
#include <unordered_map>

// Additions to enum OpCode in vm.h:
enum OpCode {
    OP_CONSTANT,
    OP_LOAD_VAR,
    OP_STORE_VAR,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_PRINT,
    OP_JUMP,            // Unconditional jump
    OP_JUMP_IF_FALSE,   // Conditional jump for if/while
    OP_HALT
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
