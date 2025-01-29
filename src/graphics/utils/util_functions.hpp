#pragma once

#include <cmath>

namespace utils
{
    constexpr double EPSILON{ 1e-6 };    // Tolerance value for relative double comparison

    // Uses relative comparison for two floating point numbers to determine if they are equal
    bool areEqual(double f1, double f2);

    // Scales a value relative to some maximum, clamping any values higher or lower than the bounds
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