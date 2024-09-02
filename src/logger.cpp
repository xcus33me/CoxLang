#include "logger.hpp"

#include "fmt/core.h"

namespace ErrorReporter {
    void error(size_t line, std::string message) {
        report(line, "", message);
    }

    void error(Token token, std::string message) {
        if (token.type_ == TokenType::EOF_TOKEN) {
            report(token.line_, " at end", message);
        } else {
            report(token.line_, " at '" + token.lexeme_ + "'", message);
        }
    }

    void report(size_t line, std::string where, std::string message) {
        // Needs something like
        // Error: Unexpected "," in argument list.
        //
        //     15 | function(first, second,);
        //                                ^-- Here.
        //
        fmt::print("Error: {}.\n\n", message);
        fmt::print("    {} | {}\n\n", line, where);

        had_error = true;
    }
}
