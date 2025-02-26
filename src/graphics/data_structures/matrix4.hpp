#pragma once

#include <array>
#include <span>

namespace gfx {
    class Matrix4
    {
    public:
        /* Constructors */

        // Default Constructor (Identity Matrix)
        Matrix4() = default;

        // Float List Constructor
        Matrix4(const double e00, const double e01, const double e02, const double e03,
                const double e10, const double e11, const double e12, const double e13,
                const double e20, const double e21, const double e22, const double e23,
                const double e30, const double e31, const double e32, const double e33)
                : m_data{ e00, e01, e02, e03,
                          e10, e11, e12, e13,
                          e20, e21, e22, e23,
                          e30, e31, e32, e33 }
        {}

        // Span-Based Constructor
        explicit Matrix4(std::span<const double, 16> values)
                : m_data{ values[0], values[1], values[2], values[3],
                          values[4], values[5], values[6], values[7],
                          values[8], values[9], values[10], values[11],
                          values[12], values[13], values[14], values[15] }
        {}

        // Copy Constructor
        Matrix4(const Matrix4&) = default;

        /* Destructor */

        ~Matrix4() = default;

        /* Assignment Operators */

        Matrix4& operator=(const Matrix4&) = default;

        /* Accessors */

        // Returns a copy of the double stored in a given position using row-major ordering
        [[nodiscard]] double operator[](const size_t row, const size_t col) const
        { return m_data[row * 4 + col]; }

        // Returns a reference to the double stored in a given position using row-major ordering
        [[nodiscard]] double& operator[](const size_t row, const size_t col)
        { return m_data[row * 4 + col]; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Matrix4& rhs) const;

        /* Arithmetic Operator Overloads */

        Matrix4& operator*=(const Matrix4& rhs);

        /* Matrix Operations */

        // Returns true if this matrix is the identity matrix
        [[nodiscard]] bool isIdentityMatrix() const;

        // Returns the transpose of this matrix
        [[nodiscard]] Matrix4 transpose() const;

        // Returns the inverse of this matrix
        [[nodiscard]] Matrix4 inverse() const;

    private:
        /* Data Members */

        std::array<double, 16> m_data{ 1.0, 0.0, 0.0, 0.0,
                                       0.0, 1.0, 0.0, 0.0,
                                       0.0, 0.0, 1.0, 0.0,
                                       0.0, 0.0, 0.0, 1.0 };    // Initialized to the identity matrix
    };

    /* Matrix Factory Functions */

    // Returns a 4x4 matrix representing the identity matrix
    [[nodiscard]] Matrix4 createIdentityMatrix();

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
}
