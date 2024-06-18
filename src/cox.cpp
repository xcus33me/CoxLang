#include "cox.hpp"
#include "scanner.hpp"
#include "token.hpp"

// stl

#include <iostream>
#include <string>
#include <vector>

void Cox::RunFile(char* path) {

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
    }
}

void Cox::Run(const std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
}