#pragma once

#include <array>

namespace gfx
{
    class Color
    {
    public:
        /* Constructors */

        Color() = default;
        Color(const double r, const double g, const double b) : m_data{ r, g, b } {}
        Color(const Color&) = default;
        Color(Color&&) = default;

        /* Destructor */

        ~Color() = default;

        /* Assignment Operators */

        Color& operator=(const Color&) = default;
        Color& operator=(Color&&) = default;

        /* Accessors */

        [[nodiscard]] double r() const { return m_data[0]; }
        [[nodiscard]] double g() const { return m_data[1]; }
        [[nodiscard]] double b() const { return m_data[2]; }

        /* Mutators */
        void setValues(const double r, const double g, const double b)
        {
            m_data[0] = r;
            m_data[1] = g;
            m_data[2] = b;
        }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Color& rhs) const;

        /* Arithmetic Operator Overloads */

        Color& operator+=(const Color& rhs);
        Color& operator-=(const Color& rhs);
        Color& operator*=(const Color& rhs);
        Color& operator*=(double scalar);

    private:
        std::array<double, 3> m_data{ 0.0, 0.0, 0.0 };
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Color operator+(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator-(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator*(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator*(const Color& lhs, double rhs);
    [[nodiscard]] Color operator*(double lhs, const Color& rhs);


}