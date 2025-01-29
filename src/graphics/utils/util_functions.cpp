#include "util_functions.hpp"

namespace utils {
    bool areEqual(double f1, double f2)
    {
        double difference = std::abs(f1 - f2);
        if (difference <= EPSILON) {
            return true;
        }
        return difference <= EPSILON * std::fmax(std::abs(f1), std::abs(f2));
    }
}