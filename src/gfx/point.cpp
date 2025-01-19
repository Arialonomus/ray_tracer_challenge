#include "point.hpp"

#include "vector.hpp"
#include "../utils/util_functions.hpp"

// Comparison Operator
bool gfx::Point::operator==(const Point& rhs) const
{
    return utils::areEqual(m_x, rhs.x())
        && utils::areEqual(m_y, rhs.y())
        && utils::areEqual(m_z, rhs.z())
        && utils::areEqual(m_w, rhs.w());
}

// Point Reverse Translation Operator
gfx::Point gfx::Point::operator-(const Vector& vec) const
{
    return Point{ m_x - vec.x(), m_y - vec.y(), m_z - vec.z() };
}

// Point Translation Shorthand Operator
gfx::Point& gfx::Point::operator+=(const Vector& vec)
{
    m_x += vec.x();
    m_y += vec.y();
    m_z += vec.z();
    m_w += vec.w();

    return *this;
}

// Point Reverse Translation Shorthand Operator
gfx::Point& gfx::Point::operator-=(const Vector& vec)
{
    m_x -= vec.x();
    m_y -= vec.y();
    m_z -= vec.z();
    m_w -= vec.w();

    return *this;
}

// Point Translation Operator (Left-Hand Point Operand)
gfx::Point gfx::operator+(const Point& lhs, const Vector& rhs)
{
    return Point{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
}

// Point Translation Operator (Right-Hand Point Operand)
gfx::Point gfx::operator+(const Vector& lhs, const Point& rhs)
{
    return Point{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
}

// Vector Distance Operator
gfx::Vector gfx::operator-(const Point& lhs, const Point& rhs)
{
    return Vector{ lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() };
}
