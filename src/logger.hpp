#pragma once

#include <stdexcept>

#include "token.hpp"

namespace ErrorReporter {
    inline bool had_error = false;

    void error(size_t line, std::string message);
    void error(Token token, std::string message);
    void report(size_t line, std::string where, std::string message);
}