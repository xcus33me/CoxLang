#include <vector>

#include "parser.hpp"
#include "token.hpp"



std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> expr = comparation();

}

std::unique_ptr<Expr> Parser::comparation() {

}

Parser::Parser(std::vector<Token> tokens):
    tokens_(std::move(tokens)),
    current_(0) { }

bool Parser::match(std::vector<TokenType> types) {
    for (const auto& type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::is_at_end() const {
    return peek().type_ == TokenType::EOF_TOKEN;
}


bool Parser::check(TokenType type) const {
    if (is_at_end()) return false;
    return peek().type_ == type;
}

Token Parser::advance() {
    if (!is_at_end()) ++current_;
    return previous();
}

Token Parser::peek() const {
    return tokens_[current_];
}

Token Parser::previous() const {
    return tokens_[current_ - 1];
}



