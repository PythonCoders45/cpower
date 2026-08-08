#ifndef VM_H
#define VM_H

#include <vector>
#include <string>
#include <unordered_map>

enum OpCode {
    OP_CONSTANT,
    OP_PRINT,
    OP_ADD,
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
