#pragma once

#include <array>
#include <span>
#include <format>

#include "matrix4.hpp"

namespace gfx {
    class Vector4
    {
    public:
        /* Constructors */

        Vector4() = default;
        Vector4(const double x, const double y, const double z, const double w) : m_data{ x, y, z ,w } {}
        explicit Vector4(std::span<const double, 4> values);
        Vector4(const Vector4&) = default;

        /* Destructor */

        ~Vector4() = default;

        /* Assignment Operators */

        Vector4& operator=(const Vector4&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Vector4& rhs) const;

        /* Accessors */

        [[nodiscard]] double x() const { return m_data[0]; }
        [[nodiscard]] double y() const { return m_data[1]; }
        [[nodiscard]] double z() const { return m_data[2]; }
        [[nodiscard]] double w() const { return m_data[3]; }

        /* Mutators */

        // Resets the w-value to 0, for use when it might get altered in surface normal calculations
        void resetW()
        { m_data[3] = 0.0f; }

        /* Arithmetic Operator Overloads */

        [[nodiscard]] Vector4 operator/(double scalar) const;
        [[nodiscard]] Vector4 operator-() const;
        Vector4& operator+=(const Vector4& rhs);
        Vector4& operator-=(const Vector4& rhs);
        Vector4& operator*=(double scalar);
        Vector4& operator/=(double scalar);
        Vector4& operator*=(const Matrix4& rhs);

        /* Vector Operations */

        // Returns a double representing the magnitude of the vector
        [[nodiscard]] double magnitude() const;

        // Returns a vector representing the cross product of this vector and the input vector
        [[nodiscard]] Vector4 crossProduct(const Vector4& rhs) const;

        // Returns a vector representing the reflection of this vector around an axis defined by a passed-in vector
        [[nodiscard]] Vector4 reflect(const Vector4& axis) const;

    private:
        /* Data Members */

        std::array<double, 4> m_data{ 0.0, 0.0, 0.0, 0.0 };
    };

    /* Factory Functions */

    // Returns a Vector4 representing a vector in space
    [[nodiscard]] Vector4 createVector(double x, double y, double z);

    // Returns a Vector4 representing a point in space
    [[nodiscard]] Vector4 createPoint(double x, double y, double z);

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    [[nodiscard]] Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
    [[nodiscard]] Vector4 operator*(const Vector4& lhs, double rhs);
    [[nodiscard]] Vector4 operator*(double lhs, const Vector4& rhs);
    [[nodiscard]] Vector4 operator*(const Matrix4& lhs, const Vector4& rhs);

    /* Global Vector Operations */

    // Returns a normalized version of the input vector, i.e. a vector with the
    // same direction but a magnitude of 1
    [[nodiscard]] Vector4 normalize(const Vector4& src);

    // Returns the dot product of this vector with the input vector
    [[nodiscard]] double dotProduct(const Vector4& lhs, const Vector4& rhs);
}

/* Template Specializations */

// Specialization of std::formatter for Vector4
template<>
struct std::formatter<gfx::Vector4> : std::formatter<std::string>
{
    auto format(const gfx::Vector4& vec, auto& ctx) const
    {
        return std::formatter<std::string>::format(
                std::format("({}, {}, {}, {})",
                            vec.x(), vec.y(), vec.z(), vec.w()),
                            ctx);
    }
};


