#include "matrix3.hpp"

#include <ranges>
#include <stdexcept>

#include "util_functions.hpp"
#include "linear_algebra.hpp"

namespace gfx {
    // Equality Operator
    bool Matrix3::operator==(const Matrix3& rhs) const
    {
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col) {
                if (utils::areNotEqual(m_data[row * 3 + col], rhs[row, col]))
                    return false;
            }
        return true;
    }

    // Matrix Multiplication Shorthand Operator
    Matrix3& Matrix3::operator*=(const Matrix3& rhs)
    {
        std::array<double, 9> matrix_product_vals{};
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col) {
                matrix_product_vals[row * 3 + col] =
                        m_data[row * 3 + 0] * rhs[0, col] +
                        m_data[row * 3 + 1] * rhs[1, col] +
                        m_data[row * 3 + 2] * rhs[2, col];
            }

        m_data = matrix_product_vals;
        return *this;
    }

    // Identity matrix identifier
    bool Matrix3::isIdentityMatrix() const
    {
        std::array<double, 9> identity_values{ 1.0, 0.0, 0.0,
                                               0.0, 1.0, 0.0,
                                               0.0, 0.0, 1.0 };
        for (int i = 0; i < 9; ++i) {
            if (utils::areNotEqual(m_data[i], identity_values[i]))
                return false;
        }
        return true;
    }

    // Matrix Transposition
    Matrix3 Matrix3::transpose() const
    {
        return Matrix3{
                m_data[0], m_data[3], m_data[6],
                m_data[1], m_data[4], m_data[7],
                m_data[2], m_data[5], m_data[8]
        };
    }

    // Matrix Inverse
    Matrix3 Matrix3::inverse() const
    {
        if (this->isIdentityMatrix())
            // Inverse of identity matrix is the identity matrix
            return Matrix3{ };

        const double determinant{ calculateDeterminant(m_data) };
        if (determinant == 0)
            // Matrix with 0 determinant is not invertible
            throw std::invalid_argument{ "Matrix determinant cannot be zero." };

        return Matrix3{ std::span<const double, 9>(calculateInverse(m_data, determinant)) };
    }

    // Matrix Multiplication Operator
    Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs)
    {
        Matrix3 return_matrix{ };
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col) {
                return_matrix[row, col] =
                        lhs[row, 0] * rhs[0, col] +
                        lhs[row, 1] * rhs[1, col] +
                        lhs[row, 2] * rhs[2, col];
            }
        return return_matrix;
    }
}