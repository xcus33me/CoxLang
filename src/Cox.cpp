#include "Cox.hpp"
#include "Error.hpp"
#include "Scanner.hpp"
#include "Token.hpp"

#include "fmt/core.h"

// stl

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Cox::Cox() {
}

void Cox::RunFile(const std::string& path) {
    std::ifstream input_file(path);
    if (input_file.fail()) {
        fmt::print("Failed to open file '{}'\n", path);
        std::exit(EXIT_FAILURE);
    }

    std::stringstream source_code;
    source_code << input_file.rdbuf();

    Run(source_code.str());

    if (ErrorReporter::had_error) {
        return;
    }
}

void Cox::RunPrompt() {
    while (true) {
        fmt::print("> ");
        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }

        Run(line);
        ErrorReporter::had_error = false;
    }
}

void Cox::Run(const std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();

    // For now, just print the tokens
    for (const Token& token : tokens) {
        std::cout << token << std::endl;
        //fmt::print("{}\n", token);
    }
}