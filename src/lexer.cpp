#include "token.hpp"
#include <cstring>
#include <cctype>
#include <iostream>

class Lexer {
    std::string src;
    size_t pos = 0;
    int line = 1;
    int col = 1;

    char peek() {
        if (pos >= src.length()) return '\0';
        return src[pos];
    }

    char advance() {
        if (pos >= src.length()) return '\0';
        char c = src[pos++];
        col++;
        return c;
    }

    bool match(char expected) {
        if (peek() == '\0') return false;
        if (peek() != expected) return false;
        pos++;
        col++;
        return true;
    }

    void skipWhitespaceAndComments() {
        while (true) {
            char c = peek();
            if (c == ' ' || c == '\t' || c == '\r') {
                advance();
            } else if (c == '\n') {
                advance();
                line++;
                col = 1;
            } else if (c == '/' && pos + 1 < src.length() && src[pos + 1] == '/') {
                // Single-line comment: // ...
                while (peek() != '\n' && peek() != '\0') {
                    advance();
                }
            } else if (c == '/' && pos + 1 < src.length() && src[pos + 1] == '*') {
                // Multi-line comment: /* ... */
                advance(); advance();
                while (peek() != '\0') {
                    if (peek() == '\n') {
                        line++;
                        col = 1;
                    }
                    if (peek() == '*' && pos + 1 < src.length() && src[pos + 1] == '/') {
                        advance(); advance();
                        break;
                    }
                    advance();
                }
            } else {
                break;
            }
        }
    }

public:
    Lexer(const std::string& source) : src(source) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (pos < src.length()) {
            skipWhitespaceAndComments();
            if (pos >= src.length()) break;

            int tokenLine = line;
            int tokenCol = col;
            char c = advance();

            Token token;
            token.line = tokenLine;
            token.col = tokenCol;

            // Operators & Punctuation Switch Board
            switch (c) {
                case '=':
                    if (match('=')) { token.type = TokenType::TOKEN_EQUALS; token.text = "=="; }
                    else if (match('>')) { token.type = TokenType::TOKEN_ARROW; token.text = "=>"; }
                    else { token.type = TokenType::TOKEN_ASSIGN; token.text = "="; }
                    tokens.push_back(token);
                    continue;
                case '+':
                    if (match('+')) { token.type = TokenType::TOKEN_INCREMENT; token.text = "++"; }
                    else if (match('=')) { token.type = TokenType::TOKEN_PLUS_ASSIGN; token.text = "+="; }
                    else { token.type = TokenType::TOKEN_PLUS; token.text = "+"; }
                    tokens.push_back(token);
                    continue;
                case '-':
                    if (match('-')) { token.type = TokenType::TOKEN_DECREMENT; token.text = "--"; }
                    else if (match('=')) { token.type = TokenType::TOKEN_MINUS_ASSIGN; token.text = "-="; }
                    else { token.type = TokenType::TOKEN_MINUS; token.text = "-"; }
                    tokens.push_back(token);
                    continue;
                case '*':
                    if (match('=')) { token.type = TokenType::TOKEN_MUL_ASSIGN; token.text = "*="; }
                    else { token.type = TokenType::TOKEN_MULTIPLY; token.text = "*"; }
                    tokens.push_back(token);
                    continue;
                case '/':
                    if (match('=')) { token.type = TokenType::TOKEN_DIV_ASSIGN; token.text = "/="; }
                    else { token.type = TokenType::TOKEN_DIVIDE; token.text = "/"; }
                    tokens.push_back(token);
                    continue;
                case '<':
                    if (match('=')) { token.type = TokenType::TOKEN_LTE; token.text = "<="; }
                    else { token.type = TokenType::TOKEN_LT; token.text = "<"; }
                    tokens.push_back(token);
                    continue;
                case '>':
                    if (match('=')) { token.type = TokenType::TOKEN_GTE; token.text = ">="; }
                    else { token.type = TokenType::TOKEN_GT; token.text = ">"; }
                    tokens.push_back(token);
                    continue;
                case '!':
                    if (match('=')) { token.type = TokenType::TOKEN_NOT_EQUALS; token.text = "!="; }
                    else { token.type = TokenType::TOKEN_NOT; token.text = "!"; }
                    tokens.push_back(token);
                    continue;
                case '&':
                    if (match('&')) { token.type = TokenType::TOKEN_LOGICAL_AND; token.text = "&&"; }
                    else { token.type = TokenType::TOKEN_BITWISE_AND; token.text = "&"; }
                    tokens.push_back(token);
                    continue;
                case '|':
                    if (match('|')) { token.type = TokenType::TOKEN_LOGICAL_OR; token.text = "||"; }
                    else { token.type = TokenType::TOKEN_BITWISE_OR; token.text = "|"; }
                    tokens.push_back(token);
                    continue;
                case ';': token.type = TokenType::TOKEN_SEMICOLON; token.text = ";"; tokens.push_back(token); continue;
                case ':': token.type = TokenType::TOKEN_COLON; token.text = ":"; tokens.push_back(token); continue;
                case ',': token.type = TokenType::TOKEN_COMMA; token.text = ","; tokens.push_back(token); continue;
                case '.': token.type = TokenType::TOKEN_DOT; token.text = "."; tokens.push_back(token); continue;
                case '{': token.type = TokenType::TOKEN_LBRACE; token.text = "{"; tokens.push_back(token); continue;
                case '}': token.type = TokenType::TOKEN_RBRACE; token.text = "}"; tokens.push_back(token); continue;
                case '(': token.type = TokenType::TOKEN_LPAREN; token.text = "("; tokens.push_back(token); continue;
                case ')': token.type = TokenType::TOKEN_RPAREN; token.text = ")"; tokens.push_back(token); continue;
                case '[': token.type = TokenType::TOKEN_LBRACKET; token.text = "["; tokens.push_back(token); continue;
                case ']': token.type = TokenType::TOKEN_RBRACKET; token.text = "]"; tokens.push_back(token); continue;
            }

            // String Literals
            if (c == '"') {
                std::string lexeme = "\"";
                while (peek() != '"' && peek() != '\0') {
                    char current = advance();
                    if (current == '\\' && peek() != '\0') {
                        char escape = advance();
                        if (escape == 'n') lexeme += '\n';
                        else if (escape == 't') lexeme += '\t';
                        else if (escape == 'r') lexeme += '\r';
                        else if (escape == '"') lexeme += '"';
                        else if (escape == '\\') lexeme += '\\';
                        else { lexeme += '\\'; lexeme += escape; }
                    } else {
                        lexeme += current;
                    }
                }
                if (peek() == '"') {
                    advance();
                    lexeme += '"';
                }
                token.type = TokenType::TOKEN_LITERAL_STRING;
                token.text = lexeme;
                tokens.push_back(token);
                continue;
            }

            // Number Literals (Integers & Floats)
            if (isdigit(c)) {
                std::string lexeme = "";
                lexeme += c;
                while (isdigit(peek())) {
                    lexeme += advance();
                }
                if (peek() == '.' && pos + 1 < src.length() && isdigit(src[pos + 1])) {
                    lexeme += advance(); // '.'
                    while (isdigit(peek())) {
                        lexeme += advance();
                    }
                    token.type = TokenType::TOKEN_FLOAT;
                } else {
                    token.type = TokenType::TOKEN_NUMBER;
                }
                token.text = lexeme;
                tokens.push_back(token);
                continue;
            }

            // Identifiers and Keywords
            if (isalpha(c) || c == '_') {
                std::string lexeme = "";
                lexeme += c;
                while (isalnum(peek()) || peek() == '_') {
                    lexeme += advance();
                }
                token.text = lexeme;

                if (lexeme == "int") token.type = TokenType::KEYWORD_INT;
                else if (lexeme == "string") token.type = TokenType::KEYWORD_STRING;
                else if (lexeme == "bool") token.type = TokenType::KEYWORD_BOOL;
                else if (lexeme == "void") token.type = TokenType::KEYWORD_VOID;
                else if (lexeme == "print") token.type = TokenType::KEYWORD_PRINT;
                else if (lexeme == "if") token.type = TokenType::KEYWORD_IF;
                else if (lexeme == "else") token.type = TokenType::KEYWORD_ELSE;
                else if (lexeme == "while") token.type = TokenType::KEYWORD_WHILE;
                else if (lexeme == "for") token.type = TokenType::KEYWORD_FOR;
                else if (lexeme == "break") token.type = TokenType::KEYWORD_BREAK;
                else if (lexeme == "continue") token.type = TokenType::KEYWORD_CONTINUE;
                else if (lexeme == "class") token.type = TokenType::KEYWORD_CLASS;
                else if (lexeme == "enum") token.type = TokenType::KEYWORD_ENUM;
                else if (lexeme == "List") token.type = TokenType::KEYWORD_LIST;
                else if (lexeme == "Dictionary") token.type = TokenType::KEYWORD_DICTIONARY;
                else if (lexeme == "public") token.type = TokenType::KEYWORD_PUBLIC;
                else if (lexeme == "private") token.type = TokenType::KEYWORD_PRIVATE;
                else if (lexeme == "return") token.type = TokenType::KEYWORD_RETURN;
                else token.type = TokenType::TOKEN_IDENTIFIER;

                tokens.push_back(token);
                continue;
            }

            // Unknown Token Fallback
            token.type = TokenType::TOKEN_UNKNOWN;
            token.text = std::string(1, c);
            tokens.push_back(token);
        }

        Token eofToken;
        eofToken.type = TokenType::TOKEN_EOF;
        eofToken.text = "EOF";
        eofToken.line = line;
        eofToken.col = col;
        tokens.push_back(eofToken);

        return tokens;
    }
};
