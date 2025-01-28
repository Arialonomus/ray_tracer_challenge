#include "gtest/gtest.h"
#include "matrix3.hpp"

#include "matrix2.hpp"

// Tests the default constructor
TEST(GraphicsMatrix3, DefaultConstructor)
{
    const gfx::Matrix3 matrix;

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, 0.0);
        }
}

// Tests the float list constructor
TEST(GraphicsMatrix3, FloatListConstructor)
{
    std::array<const float, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the span-based constructor
TEST(GraphicsMatrix3, SpanConstructor)
{
    std::array<const float, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix{ matrix_values };

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the copy constructor
TEST(GraphicsMatrix3, CopyConstructor)
{
    std::array<const float, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_a{ matrix_values} ;
    const gfx::Matrix3 matrix_b{ matrix_a };

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const float value = matrix_b[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the assignment operator
TEST(GraphicsMatrix3, AssignmentOperator)
{
    std::array<const float, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_a{ matrix_values };
    gfx::Matrix3 matrix_b{ };

    matrix_b = matrix_a;

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const float value = matrix_b[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the equality operator
TEST(GraphicsMatrix3, EqualityOperator)
{
    const gfx::Matrix3 matrix_a{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_b{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };

    ASSERT_TRUE(matrix_a == matrix_b);
}

// Tests the inequality operator
TEST(GraphicsMatrix3, InequalityOperator)
{
    const gfx::Matrix3 matrix_a{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_b{ };

    ASSERT_TRUE(matrix_a != matrix_b);
}

// Tests generating a 2x2 submatrix
TEST(GraphicsMatrix3, Submatrix)
{
    const gfx::Matrix3 matrix{
            1.0, 5.0, 0.0,
            -3.0, 2.0, 7.0,
            0.0, 6.0, -3.0
    };
    const gfx::Matrix2 submatrix_expected{
        -3.0, 2.0,
        0.0, 6.0
    };

    const gfx::Matrix2 submatrix_actual = matrix.submatrix(0, 2);

    EXPECT_TRUE(submatrix_actual == submatrix_expected);
}

// Tests calculating the determinant of a 3x3 matrix
TEST(GraphicsMatrix3, Determinant)
{
    const gfx::Matrix3 matrix{
            1.0, 2.0, 6.0,
            -5.0, 8.0, -4.0,
            2.0, 6.0, 4.0
    };

    EXPECT_FLOAT_EQ(matrix.determinant(), -196.0);
}