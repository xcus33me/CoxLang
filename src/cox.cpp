#include "cox.hpp"
#include "scanner.hpp"
#include "token.hpp"

// stl

#include <iostream>
#include <string>
#include <vector>

void Cox::RunFile(char* path) {
    // Read bytes
    if (hadError_) {
        std::cerr << "Error executing the file.";
        std::exit(EXIT_FAILURE);
    }
}

void Cox::RunPrompt() {
    while (true) {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }

        Run(line);
        hadError_ = false;
    }
}

void Cox::Run(const std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();

    // For now, just print the tokens
    for (const Token& token : tokens) {
        std::cout << token;
    }
}

void Cox::Error(int line, const std::string& message) {
    Report(line, "", message);
}

void Cox::Report(int line, const std::string& where, const std::string& message) {
    // Needs something like
    // Error: Unexpected "," in argument list.
    //
    //     15 | function(first, second,);
    //                                ^-- Here.
    //
    std::cout << "[line " << line << "] Error" << where << ": " << message;
    hadError_ = true;
}