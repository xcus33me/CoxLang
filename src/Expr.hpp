#pragma once

#include "Token.hpp"

// stl
#include <memory>

struct Expr : public std::enable_shared_from_this<Expr> {
public:
    Expr() = default;
    virtual ~Expr() = default;

    Expr(const Expr&) = delete;
    Expr(Expr&&) = delete;
    Expr& operator=(const Expr&) = delete;
    Expr& operator=(const Expr&) = delete;

    class Binary;
    class Literal;
    class Unary;
    class Grouping;
};

struct Expr::Binary : public Expr {
public:
    Binary() = delete;
    Binary(std::shared_ptr<const Expr> left, Token op, std::shared_ptr<const Expr> right);
     
    std::shared_ptr<Expr> left_;
    Token op_;
    std::shared_ptr<Expr> right_;
};

class Expr::Literal {

};

class Expr::Unary {

};

class Expr::Grouping {

};