#include "matrix3.hpp"

#include <ranges>

// Span-Based Constructor
gfx::Matrix3::Matrix3(std::span<const float, 9> values)
{
    std::copy(values.begin(), values.end(), m_data.begin());
}