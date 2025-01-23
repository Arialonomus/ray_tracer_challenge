#include "util_functions.hpp"

bool utils::areEqual(float f1, float f2)
{
    return std::fabs(f1 - f2) <= utils::EPSILON * std::fmax(std::fabs(f1), std::fabs(f2));
}
