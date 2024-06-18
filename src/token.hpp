#pragma once

class Token {
    friend std::ofstream& operator<<(std::ostream& os, const Token& token);
};