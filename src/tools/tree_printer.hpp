#pragma once

#include <any>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "fmt/core.h"
#include "../expr.hpp"

class AstPrinter : public ExprVisitor {
public:
    void print() {
        fmt::print("{}\n", repr_);
    }

    void set_repr(const std::unique_ptr<Expr>& expr) {
        expr->accept(*this);
    }

    void visitBinaryExpr(const BinaryExpr& expr) override {
        repr_ += "( " + expr.op_.lexeme_ + " ";
        set_repr(expr.left_);
        repr_ += " ";
        set_repr(expr.right_);
        repr_ += " )";
    }

    void visitGroupingExpr(const GroupingExpr& expr) override {
        repr_ += "( group ";
        set_repr(expr.expression_);
        repr_ += " )";
    }

    void visitLiteralExpr(const LiteralExpr& expr) override {
        auto &type = expr.value_.type();

        if (type == typeid(nullptr)) {
            repr_ += "NIL";
        } else if (type == typeid(std::string)) {
            try {
                repr_ += std::any_cast<std::string>(expr.value_);
            } catch (std::bad_any_cast& e) {
                repr_ += "string_any_cast_error";
            }
        } else if (type == typeid(double)) {
            repr_ += std::to_string(std::any_cast<double>(expr.value_));
        } else if (type == typeid(bool)) {
            if (std::any_cast<bool>(expr.value_)) {
                repr_ += "TRUE";
            } else {
                repr_ += "FALSE";
            }
        } else {
            repr_ += "error_no_value_matching";
        }
    }

    void visitUnaryExpr(const UnaryExpr& expr) override {
        repr_ += "( " + expr.op_.lexeme_ + " ";
        set_repr(expr.expression_);
        repr_ += " )";
    }

    [[nodiscard]] const std::string& get() const {
        return repr_;
    }

private:
    std::string repr_ = "";
};