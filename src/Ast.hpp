#pragma once

#include "Token.hpp"
#include "Utils.hpp"

#include <variant>
#include <memory>

struct AssignExpr;
struct BinaryExpr;
struct CallExpr;
struct GetExpr;
struct GroupingExpr;
struct UnaryExpr;
struct LiteralExpr;
struct LogicalExpr;

using AssignExprPtr = std::shared_ptr<AssignExpr>;
using BinaryExprPtr = std::shared_ptr<BinaryExpr>;
using CallExprPtr = std::shared_ptr<CallExpr>;
using GetExprPtr = std::shared_ptr<GetExpr>;
using GroupingExprPtr = std::shared_ptr<GroupingExpr>;
using UnaryExprPtr = std::shared_ptr<UnaryExpr>;
using LiteralExprPtr = std::shared_ptr<LiteralExpr>;
using LogicalExprPtr = std::shared_ptr<LogicalExpr>;

using Expr = std::variant<
    AssignExprPtr,
    BinaryExprPtr,
    CallExprPtr,
    GetExprPtr,
    GroupingExprPtr,
    UnaryExprPtr,
    LiteralExprPtr,
    LogicalExprPtr>;


struct Assignable : private Uncopyable {
    Token name;
    mutable signed long distance = -1;
    mutable bool isCaptured = false;

    explicit Assignable(const Token& name) : name{name} {
    }
};

struct AssignExpr final : Assignable {
    Expr value_;
    
    explicit AssignExpr(const Token& name, Expr value) : Assignable(name), value_{std::move(value)} {
    }
};

struct BinaryExpr final {
    Expr left_;
    Token op_;
    Expr right_;

    explicit BinaryExpr(Expr left, const Token& op, Expr right)
        : left_(std::move(left)), op_{op}, right_(std::move(right)) {}
};

struct UnaryExpr final {
    Expr expr_;
    Token op_;

    explicit UnaryExpr(const Token& op, Expr expr)
        : expr_(std::move(expr)), op_{op} {}
};