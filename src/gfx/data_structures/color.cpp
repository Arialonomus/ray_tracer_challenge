#include "color.hpp"

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Color::operator==(const Color& rhs) const
    {
        return utils::areEqual(m_r, rhs.r())
               && utils::areEqual(m_g, rhs.g())
               && utils::areEqual(m_b, rhs.b());
    }
    
    // Addition Shorthand Operator
    Color& Color::operator+=(const Color& rhs)
    {
        m_r += rhs.r();
        m_g += rhs.g();
        m_b += rhs.b();
    
        return *this;
    }
    
    // Subtraction Shorthand Operator
    Color& Color::operator-=(const Color& rhs)
    {
        m_r -= rhs.r();
        m_g -= rhs.g();
        m_b -= rhs.b();
    
        return *this;
    }
    
    // Color Multiplication (Hadamard Product) Shorthand Operator
    Color& Color::operator*=(const Color& rhs)
    {
        m_r *= rhs.r();
        m_g *= rhs.g();
        m_b *= rhs.b();
    
        return *this;
    }
    
    // Scalar Multiplication Shorthand Operator
    Color& Color::operator*=(const float scalar)
    {
        m_r *= scalar;
        m_g *= scalar;
        m_b *= scalar;
    
        return *this;
    }
    
    // Addition Operator
    Color operator+(const Color& lhs, const Color& rhs)
    {
        return Color{ lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b() };
    }
    
    // Subtraction Operator
    Color operator-(const Color& lhs, const Color& rhs)
    {
        return Color{ lhs.r() - rhs.r(), lhs.g() - rhs.g(), lhs.b() - rhs.b() };
    }
    
    // Color Multiplication (Hadamard Product) Operator
    Color operator*(const Color& lhs, const Color& rhs)
    {
        return Color{ lhs.r() * rhs.r(), lhs.g() * rhs.g(), lhs.b() * rhs.b() };
    }
    
    // Scalar Multiplication Operator (Color Left-Hand Operand)
    Color operator*(const Color& lhs, const float rhs)
    {
        return Color{ lhs.r() * rhs, lhs.g() * rhs, lhs.b() * rhs };
    }
    
    // Scalar Multiplication Operator (Color Right-Hand Operand)
    Color operator*(const float lhs, const Color& rhs)
    {
        return Color{ rhs.r() * lhs, rhs.g() * lhs, rhs.b() * lhs };
    }
}