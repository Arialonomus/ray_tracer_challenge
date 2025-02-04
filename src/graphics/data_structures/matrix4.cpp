#include "matrix4.hpp"

#include <ranges>
#include <stdexcept>

#include "util_functions.hpp"
#include "linear_algebra.hpp"

namespace gfx {
    // Span-Based Constructor
    Matrix4::Matrix4(std::span<const double, 16> values)
            : m_data{}
    {
        std::copy(values.begin(), values.end(), m_data.begin());
    }
    
    // Equality Operator
    bool Matrix4::operator==(const Matrix4& rhs) const
    {
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col) {
                if (!utils::areEqual(m_data[row * 4 + col], rhs[row, col])) {
                    return false;
                }
            }
    
        return true;
    }

    // Matrix Multiplication Shorthand Operator
    Matrix4& Matrix4::operator*=(const Matrix4& rhs)
    {
        std::array<double, 16> matrix_product_vals{};
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col) {
                matrix_product_vals[row * 4 + col] =
                        m_data[row * 4 + 0] * rhs[0, col] +
                        m_data[row * 4 + 1] * rhs[1, col] +
                        m_data[row * 4 + 2] * rhs[2, col] +
                        m_data[row * 4 + 3] * rhs[3, col];
            }

        m_data = matrix_product_vals;
        return *this;
    }

    // Identity matrix identifier
    bool Matrix4::isIdentityMatrix() const
    {
        std::array<double, 16> identity_values{ 1.0, 0.0, 0.0, 0.0,
                                               0.0, 1.0, 0.0, 0.0,
                                               0.0, 0.0, 1.0, 0.0,
                                               0.0, 0.0, 0.0, 1.0 };
        for (int i = 0; i < 16; ++i) {
            if (utils::areNotEqual(m_data[i], identity_values[i])) {
                return false;
            }
        }
        return true;
    }

    // Matrix Transposition
    Matrix4 Matrix4::transpose() const
    {
        return Matrix4{
                (*this)[0, 0], (*this)[1, 0], (*this)[2, 0], (*this)[3, 0],
                (*this)[0, 1], (*this)[1, 1], (*this)[2, 1], (*this)[3, 1],
                (*this)[0, 2], (*this)[1, 2], (*this)[2, 2], (*this)[3, 2],
                (*this)[0, 3], (*this)[1, 3], (*this)[2, 3], (*this)[3, 3]
        };
    }

    // Submatrix Generator
    std::vector<double> Matrix4::submatrix(size_t row_to_remove, size_t col_to_remove) const
    {
        return getSubmatrix(std::vector<double>{ m_data.begin(), m_data.end() },
                            row_to_remove,
                            col_to_remove);
    }
    
    // Matrix Determinant
    double Matrix4::determinant() const
    {
        return calculateDeterminant(std::vector<double>{ m_data.begin(), m_data.end() });
    }
    
    // Matrix Inverse
    Matrix4 Matrix4::inverse() const
    {
        // Return early if this matrix is the identity matrix
        if (this->isIdentityMatrix()) {
            return *this;
        }
    
        // Determine if matrix is invertible
        const double determinant = this->determinant();
        if (determinant == 0) {
            throw std::invalid_argument{ "Matrix determinant cannot be zero." };
        }
    
        // Invert matrix
        Matrix4 inverted_matrix{};
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col) {
                const double minor = calculateDeterminant(this->submatrix(row, col));
                const double cofactor = (row + col) % 2 == 0 ? minor : -minor;
                inverted_matrix[col, row] = cofactor / determinant;
            }
    
        return inverted_matrix;
    }

    // Identity Matrix Factory Function
    Matrix4 createIdentityMatrix()
    {
        return Matrix4{
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Matrix Multiplication Operator
    Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
    {
        Matrix4 return_matrix{};
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
}