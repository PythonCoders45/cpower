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
            // Inside VirtualMachine::execute(...)
            case OP_MULTIPLY: {
                int b = pop();
                int a = pop();
                push(a * b);
                break;
            }
            case OP_DIVIDE: {
                int b = pop();
                int a = pop();
                if (b == 0) {
                    std::cerr << "RuntimeError: Division by zero.\n";
                    return;
                }
                push(a / b);
                break;
            }
            case OP_JUMP: {
                uint16_t target = (bytecode[ip] << 8) | bytecode[ip + 1];
                ip = target;
                break;
            }
            case OP_JUMP_IF_FALSE: {
                uint16_t target = (bytecode[ip] << 8) | bytecode[ip + 1];
                ip += 2;
                int condition = pop();
                if (condition == 0) {
                    ip = target;
                }
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
