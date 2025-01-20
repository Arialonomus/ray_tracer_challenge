#include "vector4.hpp"

#include <stdexcept>
#include <cmath>

#include "../utils/util_functions.hpp"

// Comparison Operator
bool gfx::Vector4::operator==(const Vector4& rhs) const
{
    return utils::areEqual(m_x, rhs.x())
        && utils::areEqual(m_y, rhs.y())
        && utils::areEqual(m_z, rhs.z())
        && utils::areEqual(m_w, rhs.w());
}

// Scalar Division Operator
gfx::Vector4 gfx::Vector4::operator/(const float scalar) const
{
    if (scalar == 0.0)
    {
        throw std::invalid_argument{ "Divide by zero." };
    }
    return Vector4{ m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar };
}

// Unary Negation Operator
gfx::Vector4 gfx::Vector4::operator-() const
{
    return Vector4{ -m_x, -m_y, -m_z, -m_w };
}

// Vector Addition Shorthand Operator
gfx::Vector4& gfx::Vector4::operator+=(const Vector4& rhs)
{
    m_x += rhs.x();
    m_y += rhs.y();
    m_z += rhs.z();
    m_w += rhs.w();

    return *this;
}

// Vector Subtraction Shorthand Operator
gfx::Vector4& gfx::Vector4::operator-=(const Vector4& rhs)
{
    m_x -= rhs.x();
    m_y -= rhs.y();
    m_z -= rhs.z();
    m_w -= rhs.w();

    return *this;
}

// Scalar Multiplication Shorthand Operator
gfx::Vector4& gfx::Vector4::operator*=(const float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;

    return *this;
}

// Scalar Division Shorthand Operator
gfx::Vector4& gfx::Vector4::operator/=(const float scalar)
{
    if (scalar == 0.0)
    {
        throw std::invalid_argument{ "Divide by zero." };
    }

    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;

    return *this;
}

// Vector Magnitude
float gfx::Vector4::magnitude() const
{
    return std::sqrt(std::pow(m_x, 2) + std::pow(m_y, 2) + std::pow(m_z, 2) + std::pow(m_w, 2));
}

// Vector Cross Product
gfx::Vector4 gfx::Vector4::crossProduct(const Vector4& rhs) const
{
    return Vector4{ m_y * rhs.z() - m_z * rhs.y(), m_z * rhs.x() - m_x * rhs.z(), m_x * rhs.y() - m_y * rhs.x(), 0.0 };
}

// Returns a Vector4 representing a vector in space
gfx::Vector4 gfx::vector(const float x, const float y, const float z)
{
    return Vector4{ x, y, z, 0.0 };
}

// Returns a Vector4 representing a point in space
gfx::Vector4 gfx::point(const float x, const float y, const float z)
{
    return Vector4{ x, y, z, 1.0 };
}

// Addition Operator
gfx::Vector4 gfx::operator+(const Vector4& lhs, const Vector4& rhs)
{
    return Vector4{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w() };
}

// Subtraction Operator
gfx::Vector4 gfx::operator-(const Vector4& lhs, const Vector4& rhs)
{
    return Vector4{ lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z(), lhs.w() - rhs.w() };
}

// Scalar Multiplication Operator (Vector Left-Hand)
gfx::Vector4 gfx::operator*(const Vector4& lhs, const float rhs)
{
    return Vector4{ lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs, lhs.w() * rhs };
}

// Scalar Multiplication Operator (Vector Right-Hand)
gfx::Vector4 gfx::operator*(const float lhs, const Vector4& rhs)
{
    return rhs * lhs;
}

// Normalize Vector
gfx::Vector4 gfx::normalize(const Vector4& src)
{
    const float magnitude = src.magnitude();
    return Vector4{ src.x() / magnitude, src.y() / magnitude, src.z() / magnitude, src.w() / magnitude };
}

// Vector Dot Product
float gfx::dotProduct(const Vector4& lhs, const Vector4& rhs)
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() + lhs.w() * rhs.w();
}
