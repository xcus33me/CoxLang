#include "Error.hpp"

#include "fmt/core.h"

namespace ErrorReporter {
    void Error(int line, const std::string& message) {
        Report(line, "", message);
    }

    void Report(int line, const std::string& where, const std::string& message) {
        // Needs something like
        // Error: Unexpected "," in argument list.
        //
        //     15 | function(first, second,);
        //                                ^-- Here.
        //
        fmt::print("Debug: Report called with line={}, where={}, message={}\n", line, where, message);

        fmt::print("Error: {}.\n\n", message);
        fmt::print("    {} | {}\n\n", line, where);
        
        had_error = true;
    }

}