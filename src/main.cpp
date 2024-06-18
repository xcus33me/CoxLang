#include "cox.cpp"

// stl
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Usage: cox [script]";
        return;
    } 
    
    Cox cox;
    if (argc == 1) {
        cox.RunFile(argv[0]);
    } else {
        cox.RunPrompt();
    }
}