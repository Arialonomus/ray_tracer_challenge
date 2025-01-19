#pragma once

namespace gfx {
    class Vector
    {
    public:
        /* Constructors */

        Vector() = default;
        Vector(const float x, const float y, const float z) : m_x{ x }, m_y{ y }, m_z{ z } {}
        Vector(const float x, const float y, const float z, const float w) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ w } {}
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;

        /* Destructor */

        ~Vector() = default;

        /* Assignment Operators */

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        /* Accessors */

        [[nodiscard]] float x() const { return m_x; }
        [[nodiscard]] float y() const { return m_y; }
        [[nodiscard]] float z() const { return m_z; }
        [[nodiscard]] float w() const { return m_w; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Vector& rhs) const;

        /* Arithmetic Operator Overloads */

        [[nodiscard]] Vector operator/(float scalar) const;
        [[nodiscard]] Vector operator-() const;
        Vector& operator+=(const Vector& rhs);
        Vector& operator-=(const Vector& rhs);
        Vector& operator*=(float scalar);
        Vector& operator/=(float scalar);

        /* Vector Operations */

        // Returns a float representing the magnitude of the vector
        [[nodiscard]] float magnitude() const;

        // Returns a vector representing the cross product of this vector and the input vector
        [[nodiscard]] Vector crossProduct(const Vector& rhs) const;

    private:
        float m_x{ 0.0 };
        float m_y{ 0.0 };
        float m_z{ 0.0 };
        float m_w{ 0.0 };
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Vector operator+(const Vector& lhs, const Vector& rhs);
    [[nodiscard]] Vector operator-(const Vector& lhs, const Vector& rhs);
    [[nodiscard]] Vector operator*(const Vector& lhs, float rhs);
    [[nodiscard]] Vector operator*(float lhs, const Vector& rhs);

    /* Global Vector Operations */

    // Returns a normalized version of the input vector, i.e. a vector with the
    // same direction but a magnitude of 1
    [[nodiscard]] Vector normalize(const Vector& src);

    // Returns the dot product of this vector with the input vector
    [[nodiscard]] float dotProduct(const Vector& lhs, const Vector& rhs);
}
