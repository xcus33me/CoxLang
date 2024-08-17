#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

class Scanner {
public:
    Scanner(const std::string& source) : src_{source} { }

    Scanner(const Scanner&) = delete;
    Scanner(Scanner&&) = delete;
    
    Scanner& operator=(const Scanner&) = delete;
    Scanner& operator=(Scanner&&) = delete;

    std::vector<Token> ScanTokens();
    
private:
    [[nodiscard]] bool is_at_end() const;
    [[nodiscard]] bool is_digit(char c) const;
    [[nodiscard]] bool is_alpha(char c) const;
    [[nodiscard]] bool is_alphanumeric(char c) const;
    [[nodiscard]] char peek(bool next=false) const;

    bool match(char expected);
    char advance();

    void add_token(TokenType type);
    void add_token(TokenType type, std::any literal);

    void ScanToken();
    void ScanString();
    void ScanDigit();
    void ScanIdentifier();

private:
    const std::string src_;
    std::vector<Token> tokens_;

    size_t start_ = 0;
    size_t curr_  = 0;
    size_t line_  = 0;
};