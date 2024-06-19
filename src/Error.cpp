#include "Error.hpp"

#include <iostream>

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
        std::cout << "[line " << line << "] Error" << where << ": " << message;
        had_error = true;
    }

}