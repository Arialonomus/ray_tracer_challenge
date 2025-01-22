#include "matrix4.hpp"

#include <ranges>

// Standard Constructor
gfx::Matrix4::Matrix4(std::span<const float, 16> values)
        : m_data{ }, m_grid{ m_data.data() }
{
    std::copy(values.begin(), values.end(), m_data.begin());
}

// Copy Assignment Operator
gfx::Matrix4& gfx::Matrix4::operator=(const gfx::Matrix4 &rhs)
{
    if (this != &rhs) {
        m_data = rhs.m_data;
        m_grid = std::mdspan<float, std::extents<size_t, 4, 4>>{ m_data.data() };
    }

    return *this;
}

// Move Assignment Operator
gfx::Matrix4& gfx::Matrix4::operator=(gfx::Matrix4 &&rhs) noexcept
{
    if (this != &rhs) {
        m_data = rhs.m_data;
        m_grid = std::mdspan<float, std::extents<size_t, 4, 4>>{ m_data.data() };
    }

    return *this;
}

// Equality Operator
bool gfx::Matrix4::operator==(const gfx::Matrix4& rhs) const
{
    return m_data == rhs.m_data;
}

