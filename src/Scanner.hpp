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
    bool IsAtEnd();
    char Advance();
    void AddToken(TokenType type);
    void AddToken(TokenType type, std::any literal);
    void ScanToken();
private:
    const std::string src_;
    std::vector<Token> tokens_;

    size_t start_ = 0;
    size_t curr_  = 0;
    size_t line_  = 0;
};
