#ifndef LEXER_H
#define LEXER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    // End of File & Unknown
    TOKEN_EOF,
    TOKEN_UNKNOWN,

    // Data Types & Keywords
    TOKEN_INT,
    TOKEN_STRING,
    TOKEN_BOOL,
    TOKEN_VOID,
    TOKEN_PRINT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_CLASS,
    TOKEN_ENUM,
    TOKEN_LIST,
    TOKEN_DICTIONARY,
    TOKEN_PUBLIC,
    TOKEN_PRIVATE,
    TOKEN_RETURN,

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
    TOKEN_LOGICAL_OR,    // ||
    TOKEN_BITWISE_AND,   // &
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
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[128];
    int line;
    int col;
} Token;

// Core lexing function with comprehensive state tracking
Token next_token(const char** src, int* line_tracker, int* col_tracker);

#ifdef __cplusplus
}
#endif

#endif // LEXER_H
