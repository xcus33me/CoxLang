#include "cox.cpp"

// stl
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Usage: cox [script]";
    } else if (argc == 1) {
        Cox cox;
        cox.RunFile(argv[0]);
    }
}