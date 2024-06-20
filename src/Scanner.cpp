#include "Scanner.hpp" 
#include "Error.hpp"
#include "Token.hpp"

// stl

#include <string>
#include <vector>

bool Scanner::IsAtEnd() {
    return curr_ >= src_.length();
}

char Scanner::Advance() {
    return src_.at(curr_++);
}

void Scanner::AddToken(TokenType type) {
    AddToken(type, nullptr);
}

void Scanner::AddToken(TokenType type, std::any literal) {
    std::string text = src_.substr(start_, (curr_ - start_));
    tokens_.emplace_back(Token(type, text, literal, line_));
}

void Scanner::ScanToken() {
    char c = Advance();
    switch (c) {
        case '(': AddToken(TokenType::LEFT_PAREN); break;
        case ')': AddToken(TokenType::RIGHT_PAREN); break;
        case '{': AddToken(TokenType::LEFT_BRACE); break;
        case '}': AddToken(TokenType::RIGHT_BRACE); break;
        case ',': AddToken(TokenType::COMMA); break;
        case '.': AddToken(TokenType::DOT); break;
        case '-': AddToken(TokenType::MINUS); break;
        case '+': AddToken(TokenType::PLUS); break;
        case ';': AddToken(TokenType::SEMICOLON); break;
        case '/': AddToken(TokenType::SLASH); break;
        case '*': AddToken(TokenType::STAR); break;

        default:
            std::string err = "Invalid character: " + c;
            ErrorReporter::Error(line_, err);
            break;
    }
}

std::vector<Token> Scanner::ScanTokens() {
    while (!IsAtEnd()) {
        start_ = curr_;
        ScanToken();
    }

    tokens_.emplace_back(Token(TokenType::EOF_TOKEN, "", nullptr, line_));
    return tokens_;
}
