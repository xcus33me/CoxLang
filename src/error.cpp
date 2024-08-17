#include "error.hpp"

#include "fmt/core.h"

namespace ErrorReporter {
    void Error(size_t line, const std::string& message) {
        Report(line, "", message);
    }

    void Report(size_t line, const std::string& where, const std::string& message) {
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