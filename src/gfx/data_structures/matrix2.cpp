#include "matrix2.hpp"

#include <ranges>

#include "util_functions.hpp"

// Equality Operator
bool gfx::Matrix2::operator==(const gfx::Matrix2& rhs) const
{
    return
        utils::areEqual(m_data[0], rhs[0, 0]) &&
        utils::areEqual(m_data[1], rhs[0, 1]) &&
        utils::areEqual(m_data[2], rhs[1, 0]) &&
        utils::areEqual(m_data[3], rhs[1, 1]);
}

// Span-Based Constructor
gfx::Matrix2::Matrix2(std::span<const float, 4> values)
{
    std::copy(values.begin(), values.end(), m_data.begin());
}

