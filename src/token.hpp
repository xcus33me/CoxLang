#pragma once

enum TokenTypes {
    // Single-character tokens
    LEFT_PAREN = 0,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords
    VAR,
    AND,
    OR,
    IF,
    ELSE,
    TRUE,
    FALSE,
    NIL,
    WHILE,
    FOR,
    PRINT,
    FUN,
    RETURN,
    CLASS,
    THIS,
    SUPER,

    eof
};

struct Token {
    friend std::ofstream& operator<<(std::ostream& os, const Token& token);
};