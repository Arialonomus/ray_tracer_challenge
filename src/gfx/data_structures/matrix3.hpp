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
        Matrix3(const float e00, const float e01, const float e02,
                const float e10, const float e11, const float e12,
                const float e20, const float e21, const float e22)
                : m_data{ e00, e01, e02,
                          e10, e11, e12,
                          e20, e21, e22 }
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
