#pragma once

#include <any>

#include "expr.hpp"

class Interpreter : public ExprVisitor {
    void visitBinaryExpr(const BinaryExpr &expr) override;
    void visitUnaryExpr(const UnaryExpr &expr) override;
    void visitGroupingExpr(const GroupingExpr &expr) override;
    void visitLiteralExpr(const LiteralExpr &expr) override;
};