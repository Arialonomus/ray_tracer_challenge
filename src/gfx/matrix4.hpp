#pragma once

#include <array>
#include <span>
#include <mdspan>

namespace gfx {
    class Matrix4
    {
    public:
        /* Constructors */
        Matrix4()
                : m_data{ }, m_grid{ m_data.data() }
        {}
        explicit Matrix4(std::span<const float, 16> values);
        Matrix4(const Matrix4& src)
                : m_data{ src.m_data }, m_grid{ m_data.data() }
        {}
        Matrix4(const Matrix4&& src) noexcept
                : m_data{ src.m_data }, m_grid{ m_data.data() }
        {}

        /* Destructor */

        ~Matrix4() = default;

        /* Assignment Operators */

        Matrix4& operator=(const Matrix4& rhs);
        Matrix4& operator=(Matrix4&& rhs) noexcept;

        /* Comparison Operators */

        [[nodiscard]] bool operator==(const Matrix4& rhs) const;

        /* Accessors */

        // Returns a reference to the float stored in a given position using row-major ordering
        [[nodiscard]] float& operator[](const size_t row, const size_t col) const
        { return m_grid[row, col]; }

    private:
        std::array<float, 16> m_data;
        std::mdspan<float, std::extents<size_t, 4, 4>> m_grid;
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
};