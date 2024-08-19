#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "cox_interpreter.hpp"
#include "logger.hpp"
#include "scanner.hpp"
#include "token.hpp"

#include "fmt/core.h"

void Cox::run_file(const std::string& path) {
    std::ifstream input_file(path);
    if (input_file.fail()) {
        fmt::print("Failed to open file '{}'\n", path);
        std::exit(EXIT_FAILURE);
    }

    std::stringstream source_code;
    source_code << input_file.rdbuf();

    run(source_code.str());

    if (ErrorReporter::had_error) {
        return;
    }
}

void Cox::run_prompt() {
    while (true) {
        fmt::print("> ");
        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }

        run(line);
        ErrorReporter::had_error = false;
    }
}

void Cox::run(const std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();

    // For now, just print the tokens
    for (const Token& token : tokens) {
        std::cout << token << std::endl;
        //fmt::print("{}\n", token);
    }
}