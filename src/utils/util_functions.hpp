#pragma once

#include <cmath>
#include <limits>

namespace utils
{
    // Uses relative comparison for two floating point numbers to determine if they are equal
    template<typename T>
    bool areEqual(T f1, T f2)
    {
        return std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(std::fabs(f1), std::fabs(f2));
    }
    
}