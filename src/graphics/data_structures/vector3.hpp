#pragma once

#include <array>
#include <span>
#include <format>

namespace gfx {
    /* Forward Declarations */
    class Matrix3;

    class Vector3
    {
    public:
        /* Constructors */

        // Default Constructor
        Vector3() = default;

        // Float List Constructor
        Vector3(const double x, const double y, const double w)
                : m_data{ x, y, w }
        {}

        // Span-Based Constructor
        explicit Vector3(std::span<const double, 3> vector_values)
                : m_data{ vector_values[0], vector_values[1], vector_values[2] }
        {}

        // Copy Constructor
        Vector3(const Vector3&) = default;

        /* Destructor */

        ~Vector3() = default;

        /* Assignment Operators */

        Vector3& operator=(const Vector3&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Vector3& rhs) const;

        /* Accessors */

        [[nodiscard]] double x() const
        { return m_data[0]; }

        [[nodiscard]] double y() const
        { return m_data[1]; }

        [[nodiscard]] double w() const
        { return m_data[2]; }

        /* Arithmetic Operator Overloads */

        [[nodiscard]] Vector3 operator/(double scalar) const;
        [[nodiscard]] Vector3 operator-() const;
        Vector3& operator+=(const Vector3& rhs);
        Vector3& operator-=(const Vector3& rhs);
        Vector3& operator*=(double scalar);
        Vector3& operator/=(double scalar);
        Vector3& operator*=(const Matrix3& rhs);

        /* Vector Operations */

        // Returns a double representing the magnitude of the vector
        [[nodiscard]] double magnitude() const;

    private:
        /* Data Members */

        std::array<double, 3> m_data{ 0.0, 0.0, 0.0 };
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    [[nodiscard]] Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
    [[nodiscard]] Vector3 operator*(const Vector3& lhs, double rhs);
    [[nodiscard]] Vector3 operator*(double lhs, const Vector3& rhs);
    [[nodiscard]] Vector3 operator*(const Matrix3& lhs, const Vector3& rhs);

    /* Global Vector Operations */

    // Returns the dot product of this vector with the input vector
    [[nodiscard]] double dotProduct(const Vector3& lhs, const Vector3& rhs);
}

/* Template Specializations */

// Specialization of std::formatter for Vector3
template<>
struct std::formatter<gfx::Vector3> : std::formatter<std::string>
{
    auto format(const gfx::Vector3& vec, auto& ctx) const
    {
        return std::formatter<std::string>::format(
                std::format("({}, {}, {})",
                            vec.x(), vec.y(), vec.w()),
                ctx);
    }
};


