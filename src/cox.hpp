#pragma once

#include <string>

class Cox {
public:
    Cox() = default;

    Cox(const Cox&) = delete;
    Cox(Cox&&) = delete;
    
    Cox& operator=(const Cox&) = delete;
    Cox& operator=(Cox&&) = delete;

    void RunFile(const std::string& path);
    void RunPrompt();

private:
    void Run(const std::string& source);
};
