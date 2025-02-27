#include "vector3.hpp"

#include <stdexcept>
#include <cmath>

#include "util_functions.hpp"
#include "matrix3.hpp"

namespace gfx {
    // Comparison Operator
    bool Vector3::operator==(const Vector3& rhs) const
    {
        return utils::areEqual(m_data[0], rhs.x())
               && utils::areEqual(m_data[1], rhs.y())
               && utils::areEqual(m_data[2], rhs.w());
    }

    // Scalar Division Operator
    Vector3 Vector3::operator/(const double scalar) const
    {
        if (scalar == 0.0)
            throw std::invalid_argument{ "Divide by zero." };

        return Vector3{ m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar };
    }

    // Unary Negation Operator
    Vector3 Vector3::operator-() const
    {
        return Vector3{ -m_data[0], -m_data[1], -m_data[2] };
    }

    // Vector Addition Shorthand Operator
    Vector3& Vector3::operator+=(const Vector3& rhs)
    {
        m_data[0] += rhs.x();
        m_data[1] += rhs.y();
        m_data[2] += rhs.w();

        if (m_data[2] > 1)
            throw std::invalid_argument{ "Cannot add two points" };

        return *this;
    }

    // Vector Subtraction Shorthand Operator
    Vector3& Vector3::operator-=(const Vector3& rhs)
    {
        m_data[0] -= rhs.x();
        m_data[1] -= rhs.y();
        m_data[2] -= rhs.w();

        return *this;
    }

    // Scalar Multiplication Shorthand Operator
    Vector3& Vector3::operator*=(const double scalar)
    {
        m_data[0] *= scalar;
        m_data[1] *= scalar;
        m_data[2] *= scalar;

        return *this;
    }

    // Scalar Division Shorthand Operator
    Vector3& Vector3::operator/=(const double scalar)
    {
        if (scalar == 0.0)
            throw std::invalid_argument{ "Divide by zero." };

        m_data[0] /= scalar;
        m_data[1] /= scalar;
        m_data[2] /= scalar;

        return *this;
    }

    // Matrix-Vector Multiplication Shorthand Operator
    Vector3& Vector3::operator*=(const Matrix3& rhs)
    {
        // Populate the array with the dot product of each row with the vector
        std::array<double, 3> vector_values{};
        for (int row = 0; row < 3; ++row) {
            vector_values[row] =
                    m_data[0] * rhs[row, 0] +
                    m_data[1] * rhs[row, 1] +
                    m_data[2] * rhs[row, 2];
        }

        // Assign the new values and return
        m_data = vector_values;
        return *this;
    }

    // Vector Magnitude
    double Vector3::magnitude() const
    {
        return std::sqrt(
                std::pow(m_data[0], 2) +
                std::pow(m_data[1], 2) +
                std::pow(m_data[2], 2)
        );
    }

    // Point Factory Function
    Vector3 create2DPoint(const double u, const double v)
    {
        return Vector3{ u, v, 1.0 };
    }

    // Addition Operator
    Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        const double w_sum{ lhs.w() + rhs.w() };
        if (w_sum > 1)
            throw std::invalid_argument{ "Cannot add two points" };

        return Vector3{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), w_sum };
    }

    // Subtraction Operator
    Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3{ lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.w() - rhs.w() };
    }

    // Scalar Multiplication Operator (Vector Left-Hand)
    Vector3 operator*(const Vector3& lhs, const double rhs)
    {
        return Vector3{ lhs.x() * rhs, lhs.y() * rhs, lhs.w() * rhs };
    }

    // Scalar Multiplication Operator (Vector Right-Hand)
    Vector3 operator*(const double lhs, const Vector3& rhs)
    {
        return rhs * lhs;
    }

    // Matrix-Vector Multiplication Operator
    Vector3 operator*(const Matrix3& lhs, const Vector3& rhs)
    {
        std::array<double, 3> vector_values{};
        for (int row = 0; row < 3; ++row) {
            vector_values[row] =
                    lhs[row, 0] * rhs.x() +
                    lhs[row, 1] * rhs.y() +
                    lhs[row, 2] * rhs.w();
        }
        return Vector3{ vector_values };
    }

    // Normalize Vector
    Vector3 normalize(const Vector3& src)
    {
        const double magnitude{ src.magnitude() };
        return Vector3{ src.x() / magnitude, src.y() / magnitude, src.w() / magnitude };
    }

    // Vector Dot Product
    double dotProduct(const Vector3& lhs, const Vector3& rhs)
    {
        return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.w() * rhs.w();
    }
}