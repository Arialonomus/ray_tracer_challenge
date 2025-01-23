#include "matrix2.hpp"

#include <ranges>

// Span-Based Constructor
gfx::Matrix2::Matrix2(std::span<const float, 4> values)
{
    std::copy(values.begin(), values.end(), m_data.begin());
}