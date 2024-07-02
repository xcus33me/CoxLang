#include "Expr.hpp"

Expr::Binary::Binary(Expr left, Token op, Expr right) : Expr(left, op, right)
{}