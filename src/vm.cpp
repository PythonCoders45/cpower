#include "vm.h"
#include <iostream>

void VirtualMachine::push(int value) {
    stack.push_back(value);
}

int VirtualMachine::pop() {
    int val = stack.back();
    stack.pop_back();
    return val;
}

void VirtualMachine::execute(const std::vector<uint8_t>& bytecode, const std::vector<int>& constants) {
    size_t ip = 0;
    while (ip < bytecode.size()) {
        uint8_t instruction = bytecode[ip++];
        switch (instruction) {
            case OP_CONSTANT: {
                uint8_t constantIndex = bytecode[ip++];
                push(constants[constantIndex]);
                break;
            }
            case OP_ADD: {
                int b = pop();
                int a = pop();
                push(a + b);
                break;
            }
            case OP_PRINT: {
                int value = pop();
                std::cout << value << "\n";
                break;
            }
            case OP_HALT:
                return;
        }
    }
}
