#pragma once

#include <array>
#include <span>

#include "matrix3.hpp"

namespace gfx {
    class Matrix4
    {
    public:
        /* Constructors */
        Matrix4() = default;
        Matrix4(const float e00, const float e01, const float e02, const float e03,
                const float e10, const float e11, const float e12, const float e13,
                const float e20, const float e21, const float e22, const float e23,
                const float e30, const float e31, const float e32, const float e33)
                : m_data{ e00, e01, e02, e03,
                          e10, e11, e12, e13,
                          e20, e21, e22, e23,
                          e30, e31, e32, e33 }
        {}
        explicit Matrix4(std::span<const float, 16> values);
        Matrix4(const Matrix4&) = default;

        /* Destructor */

        ~Matrix4() = default;

        /* Assignment Operators */

        Matrix4& operator=(const Matrix4&) = default;

        /* Accessors */

        // Returns a copy of the float stored in a given position using row-major ordering
        [[nodiscard]] float operator[](const size_t row, const size_t col) const
        { return m_data[row * 4 + col]; }

        // Returns a reference to the float stored in a given position using row-major ordering
        [[nodiscard]] float& operator[](const size_t row, const size_t col)
        { return m_data[row * 4 + col]; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Matrix4& rhs) const;

        /* Arithmetic Operator Overloads */

        Matrix4& operator*=(const Matrix4& rhs);

        /* Matrix Operations */

        // Returns true if this matrix is the identity matrix
        [[nodiscard]] bool isIdentityMatrix() const;

        // Returns the transpose of this matrix
        [[nodiscard]] Matrix4 transpose() const;

        // Returns the 3x3 submatrix formed by removing the passed in row & column
        [[nodiscard]] Matrix3 submatrix(size_t row_to_remove, size_t col_to_remove) const;

        // Returns the determinant of this matrix
        [[nodiscard]] float determinant() const;

        // Returns the inverse of this matrix
        [[nodiscard]] Matrix4 inverse() const;

    private:
        /* Data Members */

        std::array<float, 16> m_data{};
    };

    /* Matrix Factory Functions */

    // Returns a 4x4 matrix representing the identity matrix
    [[nodiscard]] Matrix4 createIdentityMatrix();

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
}
