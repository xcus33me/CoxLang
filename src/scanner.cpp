#include <any>
#include <unordered_map>
#include <vector>
#include <string>

#include "scanner.hpp"
#include "error.hpp"
#include "token.hpp"

static const std::unordered_map<std::string, TokenType> KEY_WORDS = {
    {"var",      TokenType::VAR},
    {"and",      TokenType::AND},
    {"or",       TokenType::OR},
    {"if",       TokenType::IF},
    {"else",     TokenType::ELSE},
    {"true" ,    TokenType::TRUE},
    {"false",    TokenType::FALSE},
    {"nil",      TokenType::NIL},
    {"while",    TokenType::WHILE},
    {"for",      TokenType::FOR},
    {"continue", TokenType::CONTINUE},
    {"break",    TokenType::BREAK},
    {"print",    TokenType::PRINT},
    {"fun",      TokenType::FUN},
    {"return",   TokenType::RETURN},
    {"class",    TokenType::CLASS},
    {"this",     TokenType::THIS},
    {"super",    TokenType::SUPER},
};

void Scanner::ScanToken() {
    char c = advance();
    switch (c) {
        case '(': add_token(TokenType::LEFT_PAREN); break;
        case ')': add_token(TokenType::RIGHT_PAREN); break;
        case '{': add_token(TokenType::LEFT_BRACE); break;
        case '}': add_token(TokenType::RIGHT_BRACE); break;
        case ',': add_token(TokenType::COMMA); break;
        case '.': add_token(TokenType::DOT); break;
        case '-': add_token(TokenType::MINUS); break;
        case '+': add_token(TokenType::PLUS); break;
        case ';': add_token(TokenType::SEMICOLON); break;
        case '*': add_token(TokenType::STAR); break;
        
        case '!':
            add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::EQUAL);
            break;
        case '=':
            add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            add_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) {
                    advance();
                }
            } else {
                add_token(TokenType::SLASH);
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
            if (is_digit(c)) {
                ScanDigit();
                break;
            } else if (is_alpha(c)) {
                ScanIdentifier();
                break;
            } else {
                std::cout << "Unexpected char " + c;
                //ErrorReporter::Error(line_, "Unexpected character: " + c);
                return;
            }
    }
}

bool Scanner::is_at_end() const {
    return curr_ >= src_.length();
}

char Scanner::advance() {
    return src_.at(curr_++);
}

void Scanner::add_token(TokenType type) {
    add_token(type, "");
}

void Scanner::add_token(TokenType type, std::any literal) {
    std::string text = src_.substr(start_, (curr_ - start_));
    tokens_.emplace_back(type, text, std::move(literal), line_);
}

bool Scanner::match(char expected) {
    if (is_at_end()) {
        return false;
    }   
    if (src_.at(curr_) != expected) {
        return false;
    }

    ++curr_;
    return true;
}

char Scanner::peek(bool next) const {
    if (is_at_end()) {
        return '\0';
    }
    return next ? src_.at(curr_ + 1) : src_.at(curr_);
}

std::vector<Token> Scanner::ScanTokens() {
    while (!is_at_end()) {
        start_ = curr_;
        ScanToken();
    }

    tokens_.emplace_back(Token(TokenType::EOF_TOKEN, "", "", line_));
    return tokens_;
}

void Scanner::ScanString() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') {
            ++line_;
        }
        advance();
    }

    if (is_at_end()) {
        ErrorReporter::error(line_, "Unterminated string");
        return;
    }

    advance();

    std::string value = src_.substr(start_ + 1, (curr_ - start_));
    add_token(TokenType::STRING, value);
}

bool Scanner::is_digit(char c) const {
    return c >= '0' && c <= '9';
}

void Scanner::ScanDigit() {
    while (is_digit(peek()) || peek() == '.' || peek() == 'e') {
        advance();
    }

    std::any num_literal;
    try {
        num_literal = static_cast<double>(std::stold(src_.substr(start_, curr_ - start_)));
    } catch (const std::invalid_argument& e) {
        ErrorReporter::error(line_, "The number format is incorrect");
    }

    add_token(TokenType::NUMBER, num_literal);
}

bool Scanner::is_alpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

void Scanner::ScanIdentifier() {
    while(is_alphanumeric(peek())) {
        advance();
    }

    std::string word = src_.substr(start_, curr_ - start_);
    if (KEY_WORDS.find(word) != KEY_WORDS.end()) {
        add_token(KEY_WORDS.at(word));
    } else {
        add_token(TokenType::IDENTIFIER, word);
    }
}

bool Scanner::is_alphanumeric(char c) const {
    return is_alpha(c) || is_digit(c);
}