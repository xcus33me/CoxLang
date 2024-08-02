#include "Expr.hpp"

Expr::Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
        : left_(left), op_(op), right_(right) {}