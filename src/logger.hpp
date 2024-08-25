#pragma once

#include <stdexcept>

#include "token.hpp"

namespace ErrorReporter {
    inline bool had_error = false;

    void error(size_t line, const std::string& message);
    void error(const Token &token, const std::string &message);
    void report(size_t line, const std::string& where, const std::string& message);
}