#include "util_functions.hpp"

bool utils::areEqual(float f1, float f2)
{
    float difference = std::fabs(f1 - f2);
    if (difference <= utils::EPSILON) {
        return true;
    }
    return difference <= utils::EPSILON * std::fmax(std::fabs(f1), std::fabs(f2));
}
