#pragma once

#include <logger.hpp>
#include <memory>
#include <vector>

#include "expr.hpp"
#include "token.hpp"

struct ParseError : public std::runtime_error {
    ParseError(const Token& token, const std::string& message) : std::runtime_error(message) {
        ErrorReporter::error(token, message);
    };
};

/// expression     → equality ;
/// equality       → comparison ( ( "!=" | "==" ) comparison )* ;
/// comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
/// term           → factor ( ( "-" | "+" ) factor )* ;
/// factor         → unary ( ( "/" | "*" ) unary )* ;
/// unary          → ( "!" | "-" ) unary | primary ;
/// primary        → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser() = default;

private:
    std::vector<Token> tokens_;
    size_t current_ = 0;

    [[nodiscard]] bool match(std::initializer_list<TokenType> types);
    [[nodiscard]] bool is_at_end() const;
    [[nodiscard]] bool check(TokenType type) const;

    Token advance();
    [[nodiscard]] Token peek() const;
    [[nodiscard]] Token previous() const;

    Token consume(TokenType type, std::string message);

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparation();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();
};