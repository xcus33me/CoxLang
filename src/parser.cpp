#include <vector>

#include "parser.hpp"

Parser::Parser(std::vector<Token> tokens):
    tokens_(std::move(tokens)),
    current_(0) { }

bool Parser::match(std::vector<TokenType> types) const {

}

std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> expr = comparation();

}

std::unique_ptr<Expr> Parser::comparation() {

}




