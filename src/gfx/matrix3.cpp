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

// Submatrix Generator
gfx::Matrix2 gfx::Matrix3::submatrix(const size_t row_to_remove, const size_t col_to_remove) const
{
    gfx::Matrix2 return_matrix{ };

    for (int row = 0; row < 2; ++row)
        for (int col = 0; col < 2; ++col) {
            return_matrix[row, col] = m_data[(row + (row >= row_to_remove ? 1 : 0)) * 3 +
                                             (col + (col >= col_to_remove ? 1 : 0))];
        }

    return return_matrix;
}

// Matrix Minor at a Given Element
float gfx::Matrix3::minor(const size_t row, const size_t col) const
{
    return this->submatrix(row, col).determinant();
}

// Matrix Cofactor at a Given Element
float gfx::Matrix3::cofactor(const size_t row, const size_t col) const
{
    float minor = this->minor(row, col);
    if (row + col % 2 == 0) {
        return minor;
    } else {
        return -minor;
    }
}

// Matrix Determinant
float gfx::Matrix3::determinant() const
{
    return
        (*this)[0, 0] * this->cofactor(0, 0) +
        (*this)[0, 1] * this->cofactor(0, 1) +
        (*this)[0, 2] * this->cofactor(0, 2);
}

