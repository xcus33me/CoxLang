#include "cox.hpp"
#include "scanner.hpp"

// stl

#include <iostream>
#include <string>

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

void Cox::Run(std::string source) {
    Scanner scanner;
}