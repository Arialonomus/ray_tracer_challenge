#pragma once

namespace gfx
{
    class Color
    {
    public:
        /* Constructors */

        Color() = default;
        Color(const double r, const double g, const double b) : m_r{ r }, m_g{ g }, m_b{ b } {}
        Color(const Color&) = default;
        Color(Color&&) = default;

        /* Destructor */

        ~Color() = default;

        /* Assignment Operators */

        Color& operator=(const Color&) = default;
        Color& operator=(Color&&) = default;

        /* Accessors */

        [[nodiscard]] double r() const { return m_r; }
        [[nodiscard]] double g() const { return m_g; }
        [[nodiscard]] double b() const { return m_b; }

        /* Mutators */
        void setValues(const double r, const double g, const double b)
        {
            m_r = r;
            m_g = g;
            m_b = b;
        }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Color& rhs) const;

        /* Arithmetic Operator Overloads */

        Color& operator+=(const Color& rhs);
        Color& operator-=(const Color& rhs);
        Color& operator*=(const Color& rhs);
        Color& operator*=(double scalar);

    private:
        double m_r{ 0.0 };
        double m_g{ 0.0 };
        double m_b{ 0.0 };
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Color operator+(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator-(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator*(const Color& lhs, const Color& rhs);
    [[nodiscard]] Color operator*(const Color& lhs, double rhs);
    [[nodiscard]] Color operator*(double lhs, const Color& rhs);


}