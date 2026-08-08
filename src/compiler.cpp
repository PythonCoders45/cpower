#include "compiler.h"
#include "error.h"
#include <iostream>

uint8_t CPowerBytecodeCompiler::addConstant(int value) {
    constants.push_back(value);
    if (constants.size() > 255) {
        report_error(ERROR_SEMANTIC, 0, "Too many constants in one compilation unit (exceeded 255 limit).");
    }
    return static_cast<uint8_t>(constants.size() - 1);
}

void CPowerBytecodeCompiler::emit(uint8_t byte) {
    bytecode.push_back(byte);
}

void CPowerBytecodeCompiler::compileAST(const std::vector<std::unique_ptr<ASTNode>>& statements) {
    int variableSlotIndex = 0;

    for (const auto& stmt : statements) {
        // Handle Variable Declarations: e.g., int score = 42;
        if (auto varDecl = dynamic_cast<VarDeclNode*>(stmt.get())) {
            int val = std::stoi(varDecl->value);
            uint8_t constIndex = addConstant(val);

            // Emit bytecode to load constant and store into variable slot
            emit(OP_CONSTANT);
            emit(constIndex);

            // Register variable in symbol table memory slot
            symbolTable[varDecl->name] = variableSlotIndex++;
            emit(OP_STORE_VAR);
            emit(symbolTable[varDecl->name]);
        }
        // Handle Print Statements: e.g., print score;
        else if (auto printNode = dynamic_cast<PrintNode*>(stmt.get())) {
            if (symbolTable.find(printNode->variableName) != symbolTable.end()) {
                // Emit bytecode to load the variable value and print it
                emit(OP_LOAD_VAR);
                emit(symbolTable[printNode->variableName]);
                emit(OP_PRINT);
            } else {
                report_error(ERROR_RUNTIME, 0, "Undeclared variable '" + printNode->variableName + "' referenced in print statement.");
            }
        }
    }

    // Gracefully terminate execution stream
    emit(OP_HALT);
}

const std::vector<uint8_t>& CPowerBytecodeCompiler::getBytecode() const {
    return bytecode;
}

const std::vector<int>& CPowerBytecodeCompiler::getConstants() const {
    return constants;
}
