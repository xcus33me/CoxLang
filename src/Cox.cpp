#include "Cox.hpp"
#include "Scanner.hpp"
#include "Token.hpp"

// stl

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void Cox::RunFile(const std::string& path) {
    std::ifstream input_file(path);
    if (input_file.fail()) {
        std::cerr << "Failed to open file " << path << "\n";\
        return;
    }

    std::stringstream source_code;
    source_code << input_file.rdbuf();

    Run(source_code.str());

    if (hadError_) {
        return;
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
