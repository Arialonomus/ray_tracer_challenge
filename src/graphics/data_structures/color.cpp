#include "color.hpp"

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Color::operator==(const Color& rhs) const
    {
        return utils::areEqual(m_data[0], rhs.r())
               && utils::areEqual(m_data[1], rhs.g())
               && utils::areEqual(m_data[2], rhs.b());
    }
    
    // Addition Shorthand Operator
    Color& Color::operator+=(const Color& rhs)
    {
        m_data[0] += rhs.r();
        m_data[1] += rhs.g();
        m_data[2] += rhs.b();
    
        return *this;
    }
    
    // Subtraction Shorthand Operator
    Color& Color::operator-=(const Color& rhs)
    {
        m_data[0] -= rhs.r();
        m_data[1] -= rhs.g();
        m_data[2] -= rhs.b();
    
        return *this;
    }
    
    // Color Multiplication (Hadamard Product) Shorthand Operator
    Color& Color::operator*=(const Color& rhs)
    {
        m_data[0] *= rhs.r();
        m_data[1] *= rhs.g();
        m_data[2] *= rhs.b();
    
        return *this;
    }
    
    // Scalar Multiplication Shorthand Operator
    Color& Color::operator*=(const double scalar)
    {
        m_data[0] *= scalar;
        m_data[1] *= scalar;
        m_data[2] *= scalar;
    
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
    Color operator*(const Color& lhs, const double rhs)
    {
        return Color{ lhs.r() * rhs, lhs.g() * rhs, lhs.b() * rhs };
    }
    
    // Scalar Multiplication Operator (Color Right-Hand Operand)
    Color operator*(const double lhs, const Color& rhs)
    {
        return Color{ rhs.r() * lhs, rhs.g() * lhs, rhs.b() * lhs };
    }

    /* Color Factory Functions */

    Color black() { return Color{ 0, 0, 0 }; }
    Color white() { return Color{ 1, 1, 1 }; }
    Color red() { return Color{ 1, 0, 0 }; }
    Color green() { return Color{ 0, 1, 0 }; }
    Color blue() { return Color{ 0, 0, 1 }; }
    Color yellow() { return Color{ 1, 1, 0 }; }
    Color cyan() { return Color{ 0, 1, 1 }; }
    Color magenta() { return Color{ 1, 0, 1 }; }
}