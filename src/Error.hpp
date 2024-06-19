#pragma once

// stl

#include <any>
#include <stdexcept>

namespace ErrorReporter {
    inline bool had_error = false;

    void Error(int line, const std::string& message);
    void Report(int line, const std::string& where, const std::string& message);
}