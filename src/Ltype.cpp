#include "Ltype.hpp"

// stl

#include <string>
#include <variant>

// LString

LString::LString(const std::string& rhs) : str_{rhs} {}

LString::LString(std::string&& rhs) : str_(std::move(rhs)) {}

LString& LString::operator=(const LString& rhs) {
    if (this != &rhs) {
        str_ = rhs.str_;
    }

    return *this;
}

LString& LString::operator=(LString&& rhs) {
    str_ = std::move(rhs.str_);
    return *this;
}

LString::operator std::string() const {
    return str_;
}
    
LString LString::operator+(const LString& rhs) const {
    return LString(str_ + rhs.str_);
}

bool LString::operator==(const LString& rhs) const {
    return str_ == rhs.str_;
}

// Functions

std::string LiteralToString(const Literal& l) {
    return std::visit([](const auto& value) -> std::string {
        if constexpr (std::is_same_v<decltype(value), std::string) {
            return std::get<std::string>(value);
        } else if constexpr (std::is_same_v<decltype(value), double>) {
            return std::to_string(std::get<double>(value));
        }
    }, l);
}

LType LiteralToLtype(const Literal& l) {
    return std::visit([](const auto& value) -> LType {
        if constexpr (std::is_same_v<decltype(value), std::string) {
            return LString(std::get<std::string>(value));
        } else {
            return std::get<double>(value);
        }
    }, l);
}
 
std::string ValueToString(const LType& l) {
    // to do
}

std::string TypeToString(const LType& l) {
    // to do
}
