#include "color.hpp"

#include "util_functions.hpp"

// Equality Operator
bool gfx::Color::operator==(const Color& rhs) const
{
    return utils::areEqual(m_r, rhs.r())
        && utils::areEqual(m_g, rhs.g())
        && utils::areEqual(m_b, rhs.b());
}

// Addition Shorthand Operator
gfx::Color& gfx::Color::operator+=(const Color& rhs)
{
    m_r += rhs.r();
    m_g += rhs.g();
    m_b += rhs.b();

    return *this;
}

// Subtraction Shorthand Operator
gfx::Color& gfx::Color::operator-=(const Color& rhs)
{
    m_r -= rhs.r();
    m_g -= rhs.g();
    m_b -= rhs.b();

    return *this;
}

// Color Multiplication (Hadamard Product) Shorthand Operator
gfx::Color& gfx::Color::operator*=(const Color& rhs)
{
    m_r *= rhs.r();
    m_g *= rhs.g();
    m_b *= rhs.b();

    return *this;
}

// Scalar Multiplication Shorthand Operator
gfx::Color& gfx::Color::operator*=(const float scalar)
{
    m_r *= scalar;
    m_g *= scalar;
    m_b *= scalar;

    return *this;
}

// Addition Operator
gfx::Color gfx::operator+(const Color& lhs, const Color& rhs)
{
    return Color{ lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b() };
}

// Subtraction Operator
gfx::Color gfx::operator-(const Color& lhs, const Color& rhs)
{
    return Color{ lhs.r() - rhs.r(), lhs.g() - rhs.g(), lhs.b() - rhs.b() };
}

// Color Multiplication (Hadamard Product) Operator
gfx::Color gfx::operator*(const Color& lhs, const Color& rhs)
{
    return Color{ lhs.r() * rhs.r(), lhs.g() * rhs.g(), lhs.b() * rhs.b() };
}

// Scalar Multiplication Operator (Color Left-Hand Operand)
gfx::Color gfx::operator*(const Color& lhs, const float rhs)
{
    return Color{ lhs.r() * rhs, lhs.g() * rhs, lhs.b() * rhs };
}

// Scalar Multiplication Operator (Color Right-Hand Operand)
gfx::Color gfx::operator*(const float lhs, const Color& rhs)
{
    return Color{ rhs.r() * lhs, rhs.g() * lhs, rhs.b() * lhs };
}
