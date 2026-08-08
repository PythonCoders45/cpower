#include "error.h"
#include <iostream>
#include <cstdlib>

void report_error(ErrorType type, int line, const std::string& message) {
    std::string prefix;
    switch (type) {
        case ERROR_SYNTAX:   prefix = "SyntaxError"; break;
        case ERROR_SEMANTIC: prefix = "SemanticError"; break;
        case ERROR_RUNTIME:  prefix = "RuntimeError"; break;
    }

    std::cerr << "[Line " << line << "] " << prefix << ": " << message << "\n";
    
    if (type == ERROR_SYNTAX || type == ERROR_SEMANTIC) {
        std::exit(1);
    }
}
