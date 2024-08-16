#pragma once

#include "Token.hpp"
#include "Utils.hpp"
#include "Ltype.hpp"

#include <memory>

struct BinaryExpr;
struct GroupingExpr;
struct UnaryExpr;
struct LiteralExpr;

struct ExprVisitor {
    virtual void visitBinaryExpr(const BinaryExpr& expr) = 0;
    virtual void visitGroupingExpr(const GroupingExpr& expr) = 0;
    virtual void visitUnaryExpr(const UnaryExpr& expr) = 0;
    virtual void visitLiteralExpr(const LiteralExpr& expr) = 0;
};

struct Expr : private Uncopyable {
    virtual void accept(ExprVisitor& visitor) = 0;
    virtual ~Expr() = default;
};

struct BinaryExpr final : public Expr {
    std::unique_ptr<Expr> left_;
    Token op_;
    std::unique_ptr<Expr> right_;

    explicit BinaryExpr(std::unique_ptr<Expr> left, const Token& op, std::unique_ptr<Expr> right) 
        : left_(std::move(left)), op_{op}, right_(std::move(right)) {}

    void accept(ExprVisitor& visitor) override {
        // to do
    }
};

struct GroupingExpr final : public Expr {
    std::unique_ptr<Expr> expression_;

    explicit GroupingExpr(std::unique_ptr<Expr> expression)
        : expression_(std::move(expression)) {}
    
    void accept(ExprVisitor& visitor) override {
        // to do
    }
};

struct UnaryExpr final : public Expr {
    std::unique_ptr<Expr> expression_;
    Token op_;

    explicit UnaryExpr(std::unique_ptr<Expr> expression, const Token& op)
        : expression_(std::move(expression)), op_{op} {}

    void accept(ExprVisitor& visitor) override {
        // to do
    }
};

struct LiteralExpr final : public Expr {
    LType value_;

    explicit LiteralExpr(LType value)
        : value_(value) {}

    void accept(ExprVisitor& visitor) override {
        // to do
    }
};