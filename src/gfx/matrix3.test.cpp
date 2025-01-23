#include "gtest/gtest.h"

#include "matrix3.hpp"

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
