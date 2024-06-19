#include "Token.hpp"

Token::Token(TokenType type, std::string lexeme, std::any literal, size_t line) 
    : type_{type}, lexeme_{std::move(lexeme)}, literal_{std::move(literal)}, line_{line} {}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Type: " << token.type_ << ", Lexeme: " << token.lexeme_ << ", Line: " << token.line_ << std::endl;
    return os;
}
