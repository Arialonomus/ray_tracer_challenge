#pragma once

#include <cmath>
#include <limits>

namespace utils
{
    constexpr double EPSILON{ 1e-6 };

    /* Relative Comparison Functions */

    // Uses relative comparison for two floating point numbers to determine if they are equal
    template<typename T>
    bool areEqual(T f1, T f2)
    {
        const T epsilon{ EPSILON };
        const T difference = std::abs(f1 - f2);
        if (difference <= epsilon) {
            return true;
        }
        return difference <= epsilon * std::fmax(std::abs(f1), std::abs(f2));
    }

    // Uses relative comparison for floating-point numbers to determine f1 is less than f2
    template<typename T>
    bool isLess(T f1, T f2)
    {
        return !areEqual(f1, f2) && (f1 < f2);
    }

    // Uses relative comparison for floating-point numbers to determine f1 is less than f2
    template<typename T>
    bool isLessOrEqual(T f1, T f2)
    {
        return areEqual(f1, f2) || (f1 < f2);
    }

    // Uses relative comparison for floating-point numbers to determine f1 is greater than f2
    template<typename T>
    bool isGreater(T f1, T f2)
    {
        return !areEqual(f1, f2) && (f1 > f2);
    }

    // Uses relative comparison for floating-point numbers to determine f1 is greater than f2
    template<typename T>
    bool isGreaterOrEqual(T f1, T f2)
    {
        return areEqual(f1, f2) || (f1 > f2);
    }

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