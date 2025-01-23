#pragma once

#include <array>
#include <span>

#include "vector4.hpp"
#include "matrix3.hpp"

namespace gfx {
    class Matrix4
    {
    public:
        /* Constructors */
        Matrix4() = default;
        Matrix4(const float a, const float b, const float c, const float d,
                const float e, const float f, const float g, const float h,
                const float i, const float j, const float k, const float l,
                const float m, const float n, const float o, const float p)
                : m_data{ a, b, c, d,
                          e, f, g, h,
                          i, j, k, l,
                          m, n, o, p }
        {}
        explicit Matrix4(std::span<const float, 16> values);
        Matrix4(const Matrix4&) = default;
        Matrix4(const Matrix4&&) = default;

        /* Destructor */

        ~Matrix4() = default;

        /* Assignment Operators */

        Matrix4& operator=(const Matrix4&) = default;
        Matrix4& operator=(Matrix4&&) = default;

        /* Comparison Operators */

        [[nodiscard]] bool operator==(const Matrix4& rhs) const;

        /* Accessors */

        // Returns a copy of the float stored in a given position using row-major ordering
        [[nodiscard]] float operator[](const size_t row, const size_t col) const
        { return m_data[row * 4 + col]; }

        // Returns a reference to the float stored in a given position using row-major ordering
        [[nodiscard]] float& operator[](const size_t row, const size_t col)
        { return m_data[row * 4 + col]; }

        /* Matrix Operations */

        // Returns the transpose of this matrix
        [[nodiscard]] Matrix4 transpose() const;

        // Returns the 3x3 submatrix formed by removing the passed in row & column
        [[nodiscard]] Matrix3 submatrix(size_t row_to_remove, size_t col_to_remove) const;

    private:
        /* Data Members */

        std::array<float, 16> m_data{};
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
    [[nodiscard]] Vector4 operator*(const Matrix4& lhs, const Vector4& rhs);
};
