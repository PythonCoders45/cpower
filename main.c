#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

// Helper function to convert token types to readable strings for debugging
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_BOOL: return "TOKEN_BOOL";
        case TOKEN_VOID: return "TOKEN_VOID";
        case TOKEN_PRINT: return "TOKEN_PRINT";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_WHILE: return "TOKEN_WHILE";
        case TOKEN_FOR: return "TOKEN_FOR";
        case TOKEN_BREAK: return "TOKEN_BREAK";
        case TOKEN_CONTINUE: return "TOKEN_CONTINUE";
        case TOKEN_CLASS: return "TOKEN_CLASS";
        case TOKEN_ENUM: return "TOKEN_ENUM";
        case TOKEN_LIST: return "TOKEN_LIST";
        case TOKEN_DICTIONARY: return "TOKEN_DICTIONARY";
        case TOKEN_PUBLIC: return "TOKEN_PUBLIC";
        case TOKEN_PRIVATE: return "TOKEN_PRIVATE";
        case TOKEN_RETURN: return "TOKEN_RETURN";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER: return "TOKEN_NUMBER";
        case TOKEN_FLOAT: return "TOKEN_FLOAT";
        case TOKEN_LITERAL_STRING: return "TOKEN_LITERAL_STRING";
        case TOKEN_ASSIGN: return "TOKEN_ASSIGN";
        case TOKEN_EQUALS: return "TOKEN_EQUALS";
        case TOKEN_ARROW: return "TOKEN_ARROW";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_INCREMENT: return "TOKEN_INCREMENT";
        case TOKEN_PLUS_ASSIGN: return "TOKEN_PLUS_ASSIGN";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_DECREMENT: return "TOKEN_DECREMENT";
        case TOKEN_MINUS_ASSIGN: return "TOKEN_MINUS_ASSIGN";
        case TOKEN_MULTIPLY: return "TOKEN_MULTIPLY";
        case TOKEN_MUL_ASSIGN: return "TOKEN_MUL_ASSIGN";
        case TOKEN_DIVIDE: return "TOKEN_DIVIDE";
        case TOKEN_DIV_ASSIGN: return "TOKEN_DIV_ASSIGN";
        case TOKEN_LT: return "TOKEN_LT";
        case TOKEN_LTE: return "TOKEN_LTE";
        case TOKEN_GT: return "TOKEN_GT";
        case TOKEN_GTE: return "TOKEN_GTE";
        case TOKEN_NOT: return "TOKEN_NOT";
        case TOKEN_NOT_EQUALS: return "TOKEN_NOT_EQUALS";
        case TOKEN_LOGICAL_AND: return "TOKEN_LOGICAL_AND";
        case TOKEN_BITWISE_AND: return "TOKEN_BITWISE_AND";
        case TOKEN_LOGICAL_OR: return "TOKEN_LOGICAL_OR";
        case TOKEN_BITWISE_OR: return "TOKEN_BITWISE_OR";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        case TOKEN_COLON: return "TOKEN_COLON";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_DOT: return "TOKEN_DOT";
        case TOKEN_LBRACE: return "TOKEN_LBRACE";
        case TOKEN_RBRACE: return "TOKEN_RBRACE";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_LBRACKET: return "TOKEN_LBRACKET";
        case TOKEN_RBRACKET: return "TOKEN_RBRACKET";
        case TOKEN_EOF: return "TOKEN_EOF";
        default: return "TOKEN_UNKNOWN";
    }
}

// Function to load a whole file into a dynamically allocated string buffer
char* read_entire_file(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed for file buffer.\n");
        fclose(file);
        return NULL;
    }

    long bytes_read = fread(buffer, 1, length, file);
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    // Check if the user passed a file path argument in the terminal
    if (argc < 2) {
        printf("Usage: c_power <source_file.cp>\n");
        return 1;
    }

    const char* filepath = argv[1];
    char* source_code = read_entire_file(filepath);
    if (!source_code) {
        return 1;
    }

    int line = 1;
    int col = 1;
    const char* cursor = source_code;

    printf("=== c^ Compiler Lexer Output for: %s ===\n", filepath);
    Token tok;
    do {
        tok = next_token(&cursor, &line, &col);
        printf("Line %-3d Col %-3d | Type: %-22s | Lexeme: '%s'\n", 
               tok.line, tok.col, token_type_to_string(tok.type), tok.lexeme);
    } while (tok.type != TOKEN_EOF);

    // Free the dynamically allocated file buffer
    free(source_code);
    return 0;
}
