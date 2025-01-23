#include "vector4.hpp"

#include <ranges>
#include <stdexcept>
#include <cmath>

#include "util_functions.hpp"

// Span Constructor
gfx::Vector4::Vector4(std::span<const float, 4> values)
        : m_data{ }
{
    std::copy(values.begin(), values.end(), m_data.begin());
}

// Comparison Operator
bool gfx::Vector4::operator==(const Vector4& rhs) const
{
    return utils::areEqual(m_data[0], rhs.x())
           && utils::areEqual(m_data[1], rhs.y())
           && utils::areEqual(m_data[2], rhs.z())
           && utils::areEqual(m_data[3], rhs.w());
}

// Scalar Division Operator
gfx::Vector4 gfx::Vector4::operator/(const float scalar) const
{
    if (scalar == 0.0) {
        throw std::invalid_argument{ "Divide by zero." };
    }
    return Vector4{ m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar, m_data[3] / scalar };
}

// Unary Negation Operator
gfx::Vector4 gfx::Vector4::operator-() const
{
    return Vector4{ -m_data[0], -m_data[1], -m_data[2], -m_data[3] };
}

// Vector Addition Shorthand Operator
gfx::Vector4& gfx::Vector4::operator+=(const Vector4& rhs)
{
    m_data[0] += rhs.x();
    m_data[1] += rhs.y();
    m_data[2] += rhs.z();
    m_data[3] += rhs.w();

    return *this;
}

// Vector Subtraction Shorthand Operator
gfx::Vector4& gfx::Vector4::operator-=(const Vector4& rhs)
{
    m_data[0] -= rhs.x();
    m_data[1] -= rhs.y();
    m_data[2] -= rhs.z();
    m_data[3] -= rhs.w();

    return *this;
}

// Scalar Multiplication Shorthand Operator
gfx::Vector4& gfx::Vector4::operator*=(const float scalar)
{
    m_data[0] *= scalar;
    m_data[1] *= scalar;
    m_data[2] *= scalar;
    m_data[3] *= scalar;

    return *this;
}

// Scalar Division Shorthand Operator
gfx::Vector4& gfx::Vector4::operator/=(const float scalar)
{
    if (scalar == 0.0) {
        throw std::invalid_argument{ "Divide by zero." };
    }

    m_data[0] /= scalar;
    m_data[1] /= scalar;
    m_data[2] /= scalar;
    m_data[3] /= scalar;

    return *this;
}

// Vector Magnitude
float gfx::Vector4::magnitude() const
{
    return std::sqrt(std::pow(m_data[0], 2) + std::pow(m_data[1], 2) + std::pow(m_data[2], 2) + std::pow(m_data[3], 2));
}

// Vector Cross Product
gfx::Vector4 gfx::Vector4::crossProduct(const Vector4& rhs) const
{
    return Vector4{ m_data[1] * rhs.z() - m_data[2] * rhs.y(), m_data[2] * rhs.x() - m_data[0] * rhs.z(),
                    m_data[0] * rhs.y() - m_data[1] * rhs.x(), 0.0 };
}

// Vector Factory Function
gfx::Vector4 gfx::vector(const float x, const float y, const float z)
{
    return Vector4{ x, y, z, 0.0 };
}

// Point Factory Function
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
