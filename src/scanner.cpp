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
                break;
            } else if (IsAlpha(c)) {
                ScanIdentifier();
                break;
            } else {
                std::cout << "Unexpected char " + c;
                //ErrorReporter::Error(line_, "Unexpected character: " + c);
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
    AddToken(type, "");
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

    tokens_.emplace_back(Token(TokenType::EOF_TOKEN, "", "", line_));
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
        num_literal = static_cast<double>(std::stold(src_.substr(start_, curr_ - start_)));
    } catch (const std::invalid_argument& e) {
        ErrorReporter::Error(line_, "The number format is incorrect");
    }

    AddToken(TokenType::NUMBER, num_literal);
}

bool Scanner::IsAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

void Scanner::ScanIdentifier() {
    while(IsAlphaNumeric(Peek())) {
        Advance();
    }

    std::string word = src_.substr(start_, curr_ - start_);
    if (KEY_WORDS.find(word) != KEY_WORDS.end()) {
        AddToken(KEY_WORDS.at(word));
    } else {
        AddToken(TokenType::IDENTIFIER, word);
    }
}

bool Scanner::IsAlphaNumeric(char c) const {
    return IsAlpha(c) || IsDigit(c);
}