#pragma once

#include <array>
#include <span>

#include "matrix2.hpp"

namespace gfx {
    class Matrix3
    {
    public:
        /* Constructors */

        Matrix3() = default;
        Matrix3(const float a, const float b, const float c,
                const float d, const float e, const float f,
                const float g, const float h, const float i)
                : m_data{ a, b, c,
                          d, e, f,
                          g, h, i }
        {}
        explicit Matrix3(std::span<const float, 9> values);
        Matrix3(const Matrix3&) = default;
        Matrix3(const Matrix3&&) = default;

        /* Destructor */

        ~Matrix3() = default;

        /* Assignment Operators */

        Matrix3& operator=(const Matrix3&) = default;
        Matrix3& operator=(Matrix3&&) = default;

        /* Accessors */

        // Returns a copy of the float stored in a given position using row-major ordering
        [[nodiscard]] float operator[](const size_t row, const size_t col) const
        { return m_data[row * 3 + col]; }

        // Returns a reference to the float stored in a given position using row-major ordering
        [[nodiscard]] float& operator[](const size_t row, const size_t col)
        { return m_data[row * 3 + col]; }

        /* Comparison Operators */

        [[nodiscard]] bool operator==(const Matrix3& rhs) const;

        /* Matrix Operations */

        // Returns the 2x2 submatrix formed by removing the passed in row & column
        [[nodiscard]] Matrix2 submatrix(size_t row_to_remove, size_t col_to_remove) const;

        // Returns the determinant of this matrix
        [[nodiscard]] float determinant() const;

    private:
        /* Data Members */

        std::array<float, 9> m_data{ };
    };

}
