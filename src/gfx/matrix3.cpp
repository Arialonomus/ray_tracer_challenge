#include "matrix3.hpp"

#include <ranges>

#include "util_functions.hpp"

// Equality Operator
bool gfx::Matrix3::operator==(const gfx::Matrix3& rhs) const
{
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            if (!utils::areEqual(m_data[row * 3 + col], rhs[row, col])) {
                return false;
            }
        }

    return true;
}

// Span-Based Constructor
gfx::Matrix3::Matrix3(std::span<const float, 9> values)
{
    std::copy(values.begin(), values.end(), m_data.begin());
}
