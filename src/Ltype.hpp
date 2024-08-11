#pragma once

#include "Fwd.hpp"

// stl

#include <string>
#include <variant>

class LNil {};

class LString {
public:
    LString() = default;
    ~LString() = default;

    LString(const LString& rhs) = default;
    LString(LString&& rhs) = default;

    explicit LString(const std::string& rhs);
    explicit LString(std::string&& rhs);

    LString& operator=(const LString& rhs);
    LString& operator=(LString&& rhs);

    explicit operator std::string() const;
    
    LString operator+(const LString& rhs) const;
    bool operator==(const LString& rhs) const;

private:
    std::string str_;
}; 

using Literal = std::variant<std::string, double>;

using FuncPtr = Func*;
using InstPtr = Linst*;
using ClassPtr = Lclass*;
using LfuncPtr = Lfunc*;

using LType = std::variant<
    LNil, LString, double, bool, FuncPtr, InstPtr, ClassPtr, LfuncPtr
>;

std::string LiteralToString(const Literal& l);
LType LiteralToLtype(const Literal& l);
std::string ValueToString(const LType& l);
std::string TypeToString(const LType& l);

