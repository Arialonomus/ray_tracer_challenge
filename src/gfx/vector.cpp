#include "vector.hpp"

#include <stdexcept>
#include <cmath>

#include "../utils/util_functions.hpp"

// Comparison Operator
bool gfx::Vector::operator==(const Vector& rhs) const
{
    return utils::areEqual(m_x, rhs.x())
        && utils::areEqual(m_y, rhs.y())
        && utils::areEqual(m_z, rhs.z())
        && utils::areEqual(m_w, rhs.w());
}

// Scalar Division Operator
gfx::Vector gfx::Vector::operator/(const float scalar) const
{
    if (scalar == 0.0)
    {
        throw std::invalid_argument{ "Divide by zero." };
    }
    return Vector{ m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar };
}

// Unary Negation Operator
gfx::Vector gfx::Vector::operator-() const
{
    return Vector{ -m_x, -m_y, -m_z, -m_w };
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

// Vector Subtraction Shorthand Operator
gfx::Vector& gfx::Vector::operator-=(const Vector& rhs)
{
    m_x -= rhs.x();
    m_y -= rhs.y();
    m_z -= rhs.z();
    m_w -= rhs.w();

    return *this;
}

// Scalar Multiplication Shorthand Operator
gfx::Vector& gfx::Vector::operator*=(const float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;

    return *this;
}

// Scalar Division Shorthand Operator
gfx::Vector& gfx::Vector::operator/=(const float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;

    return *this;
}

// Magnitude of the Vector
float gfx::Vector::magnitude() const
{
    return std::sqrt(std::pow(m_x, 2) + std::pow(m_y, 2) + std::pow(m_z, 2) + std::pow(m_w, 2));
}

gfx::Vector gfx::Vector::crossProduct(const Vector& rhs) const
{
    return Vector{ m_y * rhs.z() - m_z * rhs.y(), m_z * rhs.x() - m_x * rhs.z(), m_x * rhs.y() - m_y * rhs.x() };
}

// Vector Addition Operator
gfx::Vector gfx::operator+(const Vector& lhs, const Vector& rhs)
{
    return Vector{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w() };
}

// Vector Subtraction Operator
gfx::Vector gfx::operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector{ lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z(), lhs.w() - rhs.w() };
}

// Scalar Multiplication Operator (Vector Left-Hand)
gfx::Vector gfx::operator*(const Vector& lhs, const float rhs)
{
    return Vector{ lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs, lhs.w() * rhs };
}

// Scalar Multiplication Operator (Vector Right-Hand)
gfx::Vector gfx::operator*(const float lhs, const Vector& rhs)
{
    return rhs * lhs;
}

// Normalize Vector
gfx::Vector gfx::normalize(const Vector& src)
{
    const float magnitude = src.magnitude();
    return Vector{ src.x() / magnitude, src.y() / magnitude, src.z() / magnitude, src.w() / magnitude };
}

// Vector Dot Product
float gfx::dotProduct(const Vector& lhs, const Vector& rhs)
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() + lhs.w() * rhs.w();
}
