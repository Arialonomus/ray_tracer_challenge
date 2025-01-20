#include "color.hpp"

// Color Addition Shorthand Operator
gfx::Color& gfx::Color::operator+=(const Color& rhs)
{
    m_r += rhs.r();
    m_g += rhs.g();
    m_b += rhs.b();

    return *this;
}

// Color Subtraction Shorthand Operator
gfx::Color& gfx::Color::operator-=(const Color& rhs)
{
    m_r -= rhs.r();
    m_g -= rhs.g();
    m_b -= rhs.b();

    return *this;
}

// Color Addition Operator
gfx::Color gfx::operator+(const Color& lhs, const Color& rhs)
{
    return Color{ lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b() };
}

// Color Subtraction Operator
gfx::Color gfx::operator-(const Color& lhs, const Color& rhs)
{
    return Color{ lhs.r() - rhs.r(), lhs.g() - rhs.g(), lhs.b() - rhs.b() };
}
