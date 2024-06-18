#pragma once

#include <string>

class Cox {
public:
    Cox();

    Cox(const Cox&) = delete;
    Cox(Cox&&) = delete;
    
    Cox& operator=(const Cox&) = delete;
    Cox& operator=(Cox&&) = delete;

    void RunFile(char* path);
    void RunPrompt();

private:
    void Run(std::string source);
};