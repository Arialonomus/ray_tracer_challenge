#include "vector.hpp"
#include "../utils/util_functions.hpp"

// Comparison Operator
bool gfx::Vector::operator==(const Vector& rhs) const
{
    return utils::areEqual(m_x, rhs.x())
        && utils::areEqual(m_y, rhs.y())
        && utils::areEqual(m_z, rhs.z())
        && utils::areEqual(m_w, rhs.w());
}

// Vector Addition Shorthand Operator
gfx::Vector& gfx::Vector::operator+=(const Vector& rhs)
{
    m_x += rhs.x();
    m_y += rhs.y();
    m_z += rhs.z();
    m_w += rhs.w();

    return *this;
}

gfx::Vector& gfx::Vector::operator-=(const Vector& rhs)
{
    m_x -= rhs.x();
    m_y -= rhs.y();
    m_z -= rhs.z();
    m_w -= rhs.w();

    return *this;
}

// Unary Negation Operator
gfx::Vector gfx::Vector::operator-() const
{
    return Vector{ -m_x, -m_y, -m_z };
}

// Vector Addition Operator
gfx::Vector gfx::operator+(const Vector& lhs, const Vector& rhs)
{
    return gfx::Vector{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
}

// Vector Subtraction Operator
gfx::Vector gfx::operator-(const Vector& lhs, const Vector& rhs)
{
    return gfx::Vector{ lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() };
};
