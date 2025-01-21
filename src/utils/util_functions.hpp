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

    template<typename I, typename O>
    O clampedScale(I input, O min, O max)
    {
        O scaled_value = std::round(input * max);
        if (scaled_value <= min) {
            return min;
        }
        else if (scaled_value >= max) {
            return max;
        }
        else {
            return scaled_value;
        }
    }
}