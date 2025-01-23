#pragma once

#include <array>
#include <span>

#include "vector4.hpp"

namespace gfx {
    class Matrix4
    {
    public:
        /* Constructors */
        Matrix4() = default;
        Matrix4(std::span<const float, 16> values);
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

    private:
        std::array<float, 16> m_data{};
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
    [[nodiscard]] Vector4 operator*(const Matrix4& lhs, const Vector4& rhs);
};