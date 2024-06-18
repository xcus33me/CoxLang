#pragma once

#include <token.hpp>

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
    std::string src_;
};