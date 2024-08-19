#include <iostream>

#include "cox_interpreter.hpp"
#include "fmt/core.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        fmt::print("Usage: cox [path]\n");
        std::exit(EXIT_FAILURE);
    }
    
    Cox cox;
    if (argc == 2) {
        cox.run_file(argv[1]);
    } else {
        cox.run_prompt();
    }

    return 0;
}