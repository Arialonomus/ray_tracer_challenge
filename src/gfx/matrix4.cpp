#include "matrix4.hpp"

#include <ranges>
#include <vector>

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

// Matrix Multiplication Operator
gfx::Matrix4 gfx::operator*(const Matrix4& lhs, const gfx::Matrix4& rhs)
{
    gfx::Matrix4 return_matrix { };
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            return_matrix[row, col] =
                    lhs[row, 0] * rhs[0, col] +
                    lhs[row, 1] * rhs[1, col] +
                    lhs[row, 2] * rhs[2, col] +
                    lhs[row, 3] * rhs[3, col];
        }

    return return_matrix;
}

