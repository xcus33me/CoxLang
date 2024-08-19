#pragma once
#include <memory>
#include <vector>

#include "expr.hpp"
#include "token.hpp"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser() = default;

private:
    std::vector<Token> tokens_;
    size_t current_ = 0;

    [[nodiscard]] bool match(std::vector<TokenType> types) const;

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparation();
};
