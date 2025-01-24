#include "matrix4.hpp"

#include <ranges>
#include <stdexcept>

#include "util_functions.hpp"

// Span-Based Constructor
gfx::Matrix4::Matrix4(std::span<const float, 16> values)
        : m_data { }
{
    std::copy(values.begin(), values.end(), m_data.begin());
}

// Equality Operator
bool gfx::Matrix4::operator==(const gfx::Matrix4& rhs) const
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            if (!utils::areEqual(m_data[row * 4 + col], rhs[row, col])) {
                return false;
            }
        }

    return true;
}

// Matrix Transposition
gfx::Matrix4 gfx::Matrix4::transpose() const
{
    return gfx::Matrix4{
            (*this)[0, 0], (*this)[1, 0], (*this)[2, 0], (*this)[3, 0],
            (*this)[0, 1], (*this)[1, 1], (*this)[2, 1], (*this)[3, 1],
            (*this)[0, 2], (*this)[1, 2], (*this)[2, 2], (*this)[3, 2],
            (*this)[0, 3], (*this)[1, 3], (*this)[2, 3], (*this)[3, 3]
    };
}

// Submatrix Generator
gfx::Matrix3 gfx::Matrix4::submatrix(size_t row_to_remove, size_t col_to_remove) const
{
    gfx::Matrix3 return_matrix{ };

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            return_matrix[row, col] = m_data[(row + (row >= row_to_remove ? 1 : 0)) * 4 +
                                             (col + (col >= col_to_remove ? 1 : 0))];
        }

    return return_matrix;
}

// Matrix Determinant
float gfx::Matrix4::determinant() const
{
    // Calculate the cofactor for each element in the first row
    float determinant = 0;
    for (int col = 0; col < 4; ++col) {
        float minor = this->submatrix(0, col).determinant();
        determinant += m_data[col] * ((0 + col) % 2 == 0 ? minor : -minor);
    }

    return determinant;
}

// Matrix Inverse
gfx::Matrix4 gfx::Matrix4::inverse() const
{
    // Return early if this matrix is the identity matrix
    if (*this == gfx::createIdentityMatrix()) {
        return *this;
    }

    // Determine if matrix is invertible
    const float determinant = this->determinant();
    if (determinant == 0) {
        throw std::invalid_argument{ "Matrix determinant cannot be zero." };
    }

    // Invert matrix
    gfx::Matrix4 inverted_matrix{ };
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            const float minor = this->submatrix(row, col).determinant();
            const float cofactor = (row + col) % 2 == 0 ? minor : -minor;
            inverted_matrix[col, row] = cofactor / determinant;
        }

    return inverted_matrix;
}

// Identity Matrix Factory Function
gfx::Matrix4 gfx::createIdentityMatrix()
{
    return Matrix4{
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
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