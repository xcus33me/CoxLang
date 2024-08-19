#pragma once

#include <memory>
#include <any>

#include "token.hpp"
#include "utils.hpp"

struct BinaryExpr;
struct GroupingExpr;
struct UnaryExpr;
struct LiteralExpr;

struct ExprVisitor {
    virtual ~ExprVisitor() = default;

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

    explicit BinaryExpr(std::unique_ptr<Expr>& left, Token& op, std::unique_ptr<Expr>& right)
        : left_(std::move(left)), op_{op}, right_(std::move(right)) {}

    void accept(ExprVisitor& visitor) override {
        visitor.visitBinaryExpr(*this);
    }
};

struct GroupingExpr final : public Expr {
    std::unique_ptr<Expr> expression_;

    explicit GroupingExpr(std::unique_ptr<Expr>& expression)
        : expression_(std::move(expression)) {}
    
    void accept(ExprVisitor& visitor) override {
        visitor.visitGroupingExpr(*this);
    }
};

struct UnaryExpr final : public Expr {
    std::unique_ptr<Expr> expression_;
    Token op_;

    explicit UnaryExpr(std::unique_ptr<Expr> expression, const Token& op)
        : expression_(std::move(expression)), op_{op} {}

    void accept(ExprVisitor& visitor) override {
        visitor.visitUnaryExpr(*this);
    }
};

struct LiteralExpr final : public Expr {
    std::any value_;

    explicit LiteralExpr(std::any value)
        : value_(std::move(value)) {}

    void accept(ExprVisitor& visitor) override {
        visitor.visitLiteralExpr(*this);
    }
};