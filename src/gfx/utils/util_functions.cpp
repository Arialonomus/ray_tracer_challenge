#include "util_functions.hpp"

namespace utils {
    bool areEqual(float f1, float f2)
    {
        float difference = std::fabs(f1 - f2);
        if (difference <= EPSILON) {
            return true;
        }
        return difference <= EPSILON * std::fmax(std::fabs(f1), std::fabs(f2));
    }
}