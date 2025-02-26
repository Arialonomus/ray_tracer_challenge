#pragma once

#include <array>
#include <span>

namespace gfx {
    class Matrix3
    {
    public:
        /* Constructors */

        // Default Constructor (Identity Matrix)
        Matrix3() = default;

        // Float List Constructor
        Matrix3(const double e00, const double e01, const double e02,
                const double e10, const double e11, const double e12,
                const double e20, const double e21, const double e22)
                : m_data{ e00, e01, e02,
                          e10, e11, e12,
                          e20, e21, e22 }
        {}

        // Span-Based Constructor
        explicit Matrix3(std::span<const double, 9> matrix_values)
                : m_data{ matrix_values[0], matrix_values[1], matrix_values[2],
                          matrix_values[3], matrix_values[4], matrix_values[5],
                          matrix_values[6], matrix_values[7], matrix_values[8] }
        {}

        // Copy Constructor
        Matrix3(const Matrix3&) = default;

        /* Destructor */

        ~Matrix3() = default;

        /* Assignment Operators */

        Matrix3& operator=(const Matrix3&) = default;

        /* Accessors */

        // Returns a copy of the double stored in a given position using row-major ordering
        [[nodiscard]] double operator[](const size_t row, const size_t col) const
        { return m_data[row * 3 + col]; }

        // Returns a reference to the double stored in a given position using row-major ordering
        [[nodiscard]] double& operator[](const size_t row, const size_t col)
        { return m_data[row * 3 + col]; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Matrix3& rhs) const;

        /* Arithmetic Operator Overloads */

        Matrix3& operator*=(const Matrix3& rhs);

        /* Matrix Operations */

        // Returns true if this matrix is the identity matrix
        [[nodiscard]] bool isIdentityMatrix() const;

        // Returns the transpose of this matrix
        [[nodiscard]] Matrix3 transpose() const;

        // Returns the inverse of this matrix
        [[nodiscard]] Matrix3 inverse() const;

    private:
        /* Data Members */

        std::array<double, 9> m_data{ 1.0, 0.0, 0.0,
                                      0.0, 1.0, 0.0,
                                      0.0, 0.0, 1.0 };    // Initialized to the identity matrix
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs);
}
