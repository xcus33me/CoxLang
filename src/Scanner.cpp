#include "Scanner.hpp" 
#include "Error.hpp"
#include "Token.hpp"

// stl

#include <any>
#include <string>
#include <vector>

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
        case '*': AddToken(TokenType::STAR); break;
        
        case '!':
            AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::EQUAL);
            break;
        case '=':
            AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        case '/':
            if (Match('/')) {
                while (Peek() != '\n' && !IsAtEnd()) {
                    Advance();
                }
            } else {
                AddToken(TokenType::SLASH); 
            }
            break;
        case '"':
            ScanString();
            break;

        // Ignore whitespace.
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            ++line_;
            break;

        default:
            if (IsDigit(c)) {
                ScanDigit();
            } else if (IsAlpha(c)) {
                ScanIdentifier();
            } else {
                ErrorReporter::Error(line_, "Unexpected character: " + c);
                return;
            }
    }
}

bool Scanner::IsAtEnd() const {
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

bool Scanner::Match(char expected) {
    if (IsAtEnd()) {
        return false;
    }   
    if (src_.at(curr_) != expected) {
        return false;
    }

    ++curr_;
    return true;
}

char Scanner::Peek(bool next) const {
    if (IsAtEnd()) {
        return '\0';
    }
    return next ? src_.at(curr_ + 1) : src_.at(curr_);
}

std::vector<Token> Scanner::ScanTokens() {
    while (!IsAtEnd()) {
        start_ = curr_;
        ScanToken();
    }

    tokens_.emplace_back(Token(TokenType::EOF_TOKEN, "", nullptr, line_));
    return tokens_;
}

void Scanner::ScanString() {
    while (Peek() != '"' && !IsAtEnd()) {
        if (Peek() == '\n') {
            ++line_;
        }
        Advance();
    }

    if (IsAtEnd()) {
        ErrorReporter::Error(line_, "Unterminated string");
        return;
    }

    Advance();

    std::string value = src_.substr(start_ + 1, (curr_ - start_));
    AddToken(TokenType::STRING, value);
}

bool Scanner::IsDigit(char c) const {
    return c >= '0' && c <= '9';
}

void Scanner::ScanDigit() {
    while (IsDigit(Peek()) || Peek() == '.' || Peek() == 'e') {
        Advance();
    }

    std::any num_literal;
    try {
        num_literal = std::stold(src_.substr(start_, curr_ - start_));
    } catch (const std::invalid_argument& e) {
        ErrorReporter::Error(line_, "The number format is incorrect");
    }

    AddToken(TokenType::NUMBER, num_literal);
}

bool Scanner::IsAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}