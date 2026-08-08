#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

enum class TokenType {
    // End of File & Unknown
    TOKEN_EOF,
    TOKEN_UNKNOWN,

    // Data Types & Keywords
    KEYWORD_INT,
    KEYWORD_STRING,
    KEYWORD_BOOL,
    KEYWORD_VOID,
    KEYWORD_PRINT,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_WHILE,
    KEYWORD_FOR,
    KEYWORD_BREAK,
    KEYWORD_CONTINUE,
    KEYWORD_CLASS,
    KEYWORD_ENUM,
    KEYWORD_LIST,
    KEYWORD_DICTIONARY,
    KEYWORD_PUBLIC,
    KEYWORD_PRIVATE,
    KEYWORD_RETURN,

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
    std::string text;
    int line;
    int col;
};

class Lexer {
    std::string src;
    size_t pos = 0;
    int line = 1;
    int col = 1;

    char peek();
    char advance();
    bool match(char expected);
    void skipWhitespaceAndComments();

public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();
};

#endif // LEXER_HPP
