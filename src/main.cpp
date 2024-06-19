#include "Cox.cpp"

// stl
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cerr << "Usage: cox [path]";
        
    } 
    
    Cox cox;
    if (argc == 1) {
        cox.RunFile(argv[0]);
    } else {
        cox.RunPrompt();
    }

    return 0;
}