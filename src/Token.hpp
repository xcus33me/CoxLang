#pragma once

#include "fmt/core.h"

// stl

#include <any>
#include <iostream>
#include <string>

enum TokenType {
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
    CONTINUE,
    BREAK,
    PRINT,
    FUN,
    RETURN,
    CLASS,
    THIS,
    SUPER,

    EOF_TOKEN
};

struct Token {
    TokenType type_;
    std::string lexeme_;
    std::any literal_;
    size_t line_;

    Token(TokenType type, std::string lexeme, std::any literal, size_t line) 
        : type_{type}, lexeme_{std::move(lexeme)}, literal_{std::move(literal)}, line_{line} {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "Type: " << token.type_ << ", Lexeme: " << token.lexeme_ << ", Line: " << token.line_ << std::endl;
        return os;
    }
};

/*template<>
struct fmt::formatter<Token> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Token& token, FormatContext& ctx) {
        return fmt::format_to(
            ctx.out(),
            "Token(type: {}, lexeme: {}, line: {})",
            token.type_, token.lexeme_, token.line_
        );
    }
};*/
