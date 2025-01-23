#pragma once

#include <array>
#include <span>

namespace gfx {
    class Matrix2
    {
    public:
        /* Constructors */

        Matrix2() = default;
        Matrix2(const float a, const float b,
                const float c, const float d)
                : m_data{ a, b,
                          c, d }
        {}
        explicit Matrix2(std::span<const float, 4> values);
        Matrix2(const Matrix2&) = default;
        Matrix2(const Matrix2&&) = default;

        /* Destructor */

        ~Matrix2() = default;

        /* Assignment Operators */

        Matrix2& operator=(const Matrix2&) = default;
        Matrix2& operator=(Matrix2&&) = default;

        /* Accessors */

        // Returns a copy of the float stored in a given position using row-major ordering
        [[nodiscard]] float operator[](const size_t row, const size_t col) const
        { return m_data[row * 2 + col]; }

        // Returns a reference to the float stored in a given position using row-major ordering
        [[nodiscard]] float& operator[](const size_t row, const size_t col)
        { return m_data[row * 2 + col]; }

        /* Matrix Operations */

        // Returns the determinant of this matrix
        [[nodiscard]] float determinant() const { return m_data[0] * m_data[3] - m_data[1] * m_data[2]; }

    private:
        /* Data Members */

        std::array<float, 4> m_data{};
    };

}
