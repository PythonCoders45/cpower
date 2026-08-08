#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

// Strongly-typed enum class for modern C++ safety
enum class TokenType {
    // End of File & Unknown
    TOKEN_EOF,
    TOKEN_UNKNOWN,

    // Data Types & Keywords
    KEYWORD_INT,       // Maps to "int"
    KEYWORD_STRING,    // Maps to "string"
    KEYWORD_BOOL,      // Maps to "bool"
    KEYWORD_VOID,      // Maps to "void"
    KEYWORD_PRINT,     // Maps to "print"
    KEYWORD_IF,        // Maps to "if"
    KEYWORD_ELSE,      // Maps to "else"
    KEYWORD_WHILE,     // Maps to "while"
    KEYWORD_FOR,       // Maps to "for"
    KEYWORD_BREAK,     // Maps to "break"
    KEYWORD_CONTINUE,  // Maps to "continue"
    KEYWORD_CLASS,     // Maps to "class"
    KEYWORD_ENUM,      // Maps to "enum"
    KEYWORD_LIST,      // Maps to "List"
    KEYWORD_DICTIONARY,// Maps to "Dictionary"
    KEYWORD_PUBLIC,    // Maps to "public"
    KEYWORD_PRIVATE,    // Maps to "private"
    KEYWORD_RETURN,    // Maps to "return"

    // Literals & Identifiers
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_FLOAT,
    TOKEN_LITERAL_STRING,

    // Operators & Assignment
    TOKEN_ASSIGN,        // =
    TOKEN_EQUALS,        // ==
    TOKEN_NOT_EQUALS,    // !=
    TOKEN_ARROW,         // =>
    TOKEN_PLUS,          // +
    TOKEN_PLUS_ASSIGN,   // +=
    TOKEN_INCREMENT,     // ++
    TOKEN_MINUS,         // -
    TOKEN_MINUS_ASSIGN,  // -=
    TOKEN_DECREMENT,     // --
    TOKEN_MULTIPLY,      // *
    TOKEN_MUL_ASSIGN,    // *=
    TOKEN_DIVIDE,        // /
    TOKEN_DIV_ASSIGN,    // /=
    TOKEN_LT,            // <
    TOKEN_LTE,           // <=
    TOKEN_GT,            // >
    TOKEN_GTE,           // >=
    TOKEN_NOT,           // !
    TOKEN_LOGICAL_AND,   // &&
    TOKEN_BITWISE_AND,   // &
    TOKEN_LOGICAL_OR,    // ||
    TOKEN_BITWISE_OR,    // |

    // Punctuation & Delimiters
    TOKEN_SEMICOLON,     // ;
    TOKEN_COLON,         // :
    TOKEN_COMMA,         // ,
    TOKEN_DOT,           // .
    TOKEN_LBRACE,        // {
    TOKEN_RBRACE,        // }
    TOKEN_LPAREN,        // (
    TOKEN_RPAREN,        // )
    TOKEN_LBRACKET,      // [
    TOKEN_RBRACKET       // ]
};

struct Token {
    TokenType type;
    std::string text;    // Using std::string instead of a fixed char array for safety in C++
    int line;
    int col;
};

#endif // LEXER_HPP
