

#pragma once
#include <string>
#include <random>

class Die {
public:
    Die();
    int roll();
    int getValue() const;
    std::string displayValue() const;

private:
    int value;

    // A modern C++ random number generator
    // static makes it so all Die objects share one generator
    static std::mt19937 gen;
};

