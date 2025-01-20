#pragma once

namespace gfx {
    class Vector4
    {
    public:
        /* Constructors */

        Vector4() = default;
        Vector4(const float x, const float y, const float z, const float w) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ w } {}
        Vector4(const Vector4&) = default;
        Vector4(Vector4&&) = default;

        /* Destructor */

        ~Vector4() = default;

        /* Assignment Operators */

        Vector4& operator=(const Vector4&) = default;
        Vector4& operator=(Vector4&&) = default;

        /* Accessors */

        [[nodiscard]] float x() const { return m_x; }
        [[nodiscard]] float y() const { return m_y; }
        [[nodiscard]] float z() const { return m_z; }
        [[nodiscard]] float w() const { return m_w; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Vector4& rhs) const;

        /* Arithmetic Operator Overloads */

        [[nodiscard]] Vector4 operator/(float scalar) const;
        [[nodiscard]] Vector4 operator-() const;
        Vector4& operator+=(const Vector4& rhs);
        Vector4& operator-=(const Vector4& rhs);
        Vector4& operator*=(float scalar);
        Vector4& operator/=(float scalar);

        /* Vector Operations */

        // Returns a float representing the magnitude of the vector
        [[nodiscard]] float magnitude() const;

        // Returns a vector representing the cross product of this vector and the input vector
        [[nodiscard]] Vector4 crossProduct(const Vector4& rhs) const;

    private:
        float m_x{ 0.0 };
        float m_y{ 0.0 };
        float m_z{ 0.0 };
        float m_w{ 0.0 };
    };

    /* Factory Functions */

    // Returns a Vector4 representing a vector in space
    [[nodiscard]] Vector4 vector(float x, float y, float z);

    // Returns a Vector4 representing a point in space
    [[nodiscard]] Vector4 point(float x, float y, float z);

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    [[nodiscard]] Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
    [[nodiscard]] Vector4 operator*(const Vector4& lhs, float rhs);
    [[nodiscard]] Vector4 operator*(float lhs, const Vector4& rhs);

    /* Global Vector Operations */

    // Returns a normalized version of the input vector, i.e. a vector with the
    // same direction but a magnitude of 1
    [[nodiscard]] Vector4 normalize(const Vector4& src);

    // Returns the dot product of this vector with the input vector
    [[nodiscard]] float dotProduct(const Vector4& lhs, const Vector4& rhs);
}
