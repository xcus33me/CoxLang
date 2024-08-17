#pragma once

#include <stdexcept>

namespace ErrorReporter {
    inline bool had_error = false;

    void Error(size_t line, const std::string& message);
    void Report(size_t line, const std::string& where, const std::string& message);
}