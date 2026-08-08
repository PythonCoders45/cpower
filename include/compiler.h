#ifndef COMPILER_H
#define COMPILER_H

#include "parser.h"
#include "vm.h"
#include <vector>
#include <string>
#include <unordered_map>

class CPowerBytecodeCompiler {
private:
    std::vector<uint8_t> bytecode;
    std::vector<int> constants;
    std::unordered_map<std::string, int> symbolTable; // Maps variable names to local slots

    uint8_t addConstant(int value);
    void emit(uint8_t byte);

public:
    void compileAST(const std::vector<std::unique_ptr<ASTNode>>& statements);

    const std::vector<uint8_t>& getBytecode() const;
    const std::vector<int>& getConstants() const;
};

#endif // COMPILER_H
