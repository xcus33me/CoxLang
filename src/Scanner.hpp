#pragma once

#include <Token.hpp>

// stl

#include <iostream>
#include <string>
#include <vector>

class Scanner {
public:
    Scanner(const std::string& source) : src_{source} {
    }

    Scanner(const Scanner&) = delete;
    Scanner(Scanner&&) = delete;
    
    Scanner& operator=(const Scanner&) = delete;
    Scanner& operator=(Scanner&&) = delete;

    std::vector<Token> ScanTokens();
    
private:
    bool IsAtEnd() const;
    bool IsDigit(char c) const;
    bool IsAlpha(char c) const;
    bool Match(char expected);
    char Advance();
    char Peek(bool next=false) const;
    void AddToken(TokenType type);
    void AddToken(TokenType type, std::any literal);

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