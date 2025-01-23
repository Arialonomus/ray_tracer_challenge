#include "matrix4.hpp"

#include <ranges>

// Standard Constructor
gfx::Matrix4::Matrix4(std::span<const float, 16> values)
{
    std::copy(values.begin(), values.end(), m_data.begin());
}

// Equality Operator
bool gfx::Matrix4::operator==(const gfx::Matrix4& rhs) const
{
    return m_data == rhs.m_data;
}

// Matrix Multiplication Operator
gfx::Matrix4 gfx::operator*(const Matrix4& lhs, const gfx::Matrix4& rhs)
{
    gfx::Matrix4 return_matrix{ };
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

// Matrix-Vector Multiplication Operator
gfx::Vector4 gfx::operator*(const gfx::Matrix4& lhs, const gfx::Vector4& rhs)
{
    return Vector4 { };
}

