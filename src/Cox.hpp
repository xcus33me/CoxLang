#pragma once

#include <string>

class Cox {
public:
    Cox();

    Cox(const Cox&) = delete;
    Cox(Cox&&) = delete;
    
    Cox& operator=(const Cox&) = delete;
    Cox& operator=(Cox&&) = delete;

    void RunFile(const std::string& path);
    void RunPrompt();

private:
    void Run(const std::string& source);

    // Might be replaced with ErrorReporter class
    void Error(int line, const std::string& message);
    void Report(int line, const std::string& where, const std::string& message);

    bool hadError_ = false;
};
