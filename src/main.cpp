#include <iostream>

#include "Cox.hpp"
#include "fmt/core.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        fmt::print("Usage: cox [path]\n");
        std::exit(EXIT_FAILURE);
    }
    
    Cox cox;
    if (argc == 2) {
        cox.RunFile(argv[1]);
    } else {
        cox.RunPrompt();
    }

    return 0;
}