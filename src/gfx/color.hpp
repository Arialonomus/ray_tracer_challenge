#pragma once

namespace gfx
{
    class Color
    {
    public:
        /* Constructors */

        Color() = default;
        Color(const float r, const float g, const float b) : m_r{ r }, m_g{ g }, m_b{ b } {}
        Color(const Color&) = default;
        Color(Color&&) = default;

        /* Destructor */

        ~Color() = default;

        /* Assignment Operators */

        Color& operator=(const Color&) = default;
        Color& operator=(Color&&) = default;

        /* Accessors */

        [[nodiscard]] float r() const { return m_r; }
        [[nodiscard]] float g() const { return m_g; }
        [[nodiscard]] float b() const { return m_b; }

        /* Arithmetic Operator Overloads */

        Color& operator+=(const Color& rhs);
        Color& operator-=(const Color& rhs);
        Color& operator*=(float scalar);

    private:
        float m_r{ 0.0 };
        float m_g{ 0.0 };
        float m_b{ 0.0 };
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Color operator+(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator-(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator*(const Color& lhs, float rhs);
    [[nodiscard]] Color operator*(float lhs, const Color& rhs);
}