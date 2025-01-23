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

// Tests calculating the minor of an element at a given row & column
TEST(GraphicsMatrix3, Minor)
{
    const gfx::Matrix3 matrix{
            3.0, 5.0, 0.0,
            2.0, -1.0, -7.0,
            6.0, -1.0, 5.0
    };
    constexpr size_t row{ 1 };
    constexpr size_t col{ 0 };

    EXPECT_FLOAT_EQ(matrix.minor(row, col), 25.0);
}

// Tests calculating the cofactor of an element at a given row & column
TEST(GraphicsMatrix3, Cofactor)
{
    const gfx::Matrix3 matrix{
            3.0, 5.0, 0.0,
            2.0, -1.0, -7.0,
            6.0, -1.0, 5.0
    };
    constexpr size_t row_a{ 1 };
    constexpr size_t col_a{ 0 };

    EXPECT_FLOAT_EQ(matrix.cofactor(row_a, col_a), -25.0);

    constexpr size_t row_b{ 0 };
    constexpr size_t col_b{ 0 };

    EXPECT_FLOAT_EQ(matrix.cofactor(row_b, col_b), -12.0);
}