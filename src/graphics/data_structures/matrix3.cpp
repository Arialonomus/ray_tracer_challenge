#include "matrix3.hpp"

#include <ranges>

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Matrix3::operator==(const Matrix3& rhs) const
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
    Matrix3::Matrix3(std::span<const float, 9> values)
    {
        std::copy(values.begin(), values.end(), m_data.begin());
    }
    
    // Submatrix Generator
    Matrix2 Matrix3::submatrix(const size_t row_to_remove, const size_t col_to_remove) const
    {
        Matrix2 return_matrix{};
    
        for (int row = 0; row < 2; ++row)
            for (int col = 0; col < 2; ++col) {
                return_matrix[row, col] = m_data[(row + (row >= row_to_remove ? 1 : 0)) * 3 +
                                                 (col + (col >= col_to_remove ? 1 : 0))];
            }
    
        return return_matrix;
    }
    
    // Matrix Determinant
    float Matrix3::determinant() const
    {
        // Calculate the cofactor for each element in the first row
        float determinant = 0;
        for (int col = 0; col < 3; ++col) {
            float minor = this->submatrix(0, col).determinant();
            determinant += m_data[col] * (0 + col % 2 == 0 ? minor : -minor);
        }
    
        return determinant;
    }
}
