#pragma once

#include <string>

class Cox {
public:
    Cox() = default;

    Cox(const Cox&) = delete;
    Cox(Cox&&) = delete;
    
    Cox& operator=(const Cox&) = delete;
    Cox& operator=(Cox&&) = delete;

    void run_file(const std::string& path);
    void run_prompt();

private:
    void run(const std::string& source);
};
