#include "matrix4.hpp"

#include <ranges>
#include <stdexcept>

#include "util_functions.hpp"
#include "linear_algebra.hpp"

namespace gfx {
    // Equality Operator
    bool Matrix4::operator==(const Matrix4& rhs) const
    {
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col) {
                if (!utils::areEqual(m_data[row * 4 + col], rhs[row, col]))
                    return false;
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
            if (utils::areNotEqual(m_data[i], identity_values[i]))
                return false;
        }
        return true;
    }

    // Matrix Transposition
    Matrix4 Matrix4::transpose() const
    {
        return Matrix4{
                m_data[0], m_data[4], m_data[8], m_data[12],
                m_data[1], m_data[5], m_data[9], m_data[13],
                m_data[2], m_data[6], m_data[10], m_data[14],
                m_data[3], m_data[7], m_data[11], m_data[15]
        };
    }
    
    // Matrix Inverse
    Matrix4 Matrix4::inverse() const
    {
        if (this->isIdentityMatrix())
            // Inverse of identity matrix is the identity matrix
            return Matrix4{ };

        const double determinant{ calculateDeterminant(m_data) };
        if (determinant == 0)
            // Matrix with 0 determinant is not invertible
            throw std::invalid_argument{ "Matrix determinant cannot be zero." };

        return Matrix4{ std::span<const double, 16>(calculateInverse(m_data, determinant)) };
    }

    // Identity Matrix Factory Function
    Matrix4 createIdentityMatrix()
    {
        return Matrix4{ };
    }

    // Matrix Multiplication Operator
    Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
    {
        Matrix4 return_matrix{ };
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