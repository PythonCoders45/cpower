#ifndef ERROR_H
#define ERROR_H

#include <string>

enum ErrorType {
    ERROR_SYNTAX,
    ERROR_SEMANTIC,
    ERROR_RUNTIME
};

void report_error(ErrorType type, int line, const std::string& message);

#endif
