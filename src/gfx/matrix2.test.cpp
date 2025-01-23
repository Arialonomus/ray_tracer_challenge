#include "gtest/gtest.h"

#include "matrix2.hpp"

// Tests the default constructor
TEST(GraphicsMatrix2, DefaultConstructor)
{
    const gfx::Matrix2 matrix;

    for (int row = 0; row < 2; ++row)
        for (int col = 0; col < 2; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, 0.0);
        }
}

// Tests the float list constructor
TEST(GraphicsMatrix2, FloatListConstructor)
{
    std::array<const float, 4> matrix_values{
            1.0, 2.0, 3.0, 4.0,
    };
    const gfx::Matrix2 matrix{
            1.0, 2.0, 3.0, 4.0,
    };

    for (int row = 0; row < 2; ++row)
        for (int col = 0; col < 2; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 2 + col]);
        }
}

// Tests the span-based constructor
TEST(GraphicsMatrix2, SpanConstructor)
{
    std::array<const float, 4> matrix_values{
            1.0, 2.0, 3.0, 4.0
    };
    const gfx::Matrix2 matrix{ matrix_values };

    for (int row = 0; row < 2; ++row)
        for (int col = 0; col < 2; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 2 + col]);
        }
}

// Tests the copy constructor
TEST(GraphicsMatrix2, CopyConstructor)
{
    std::array<const float, 4> matrix_values{
            1.0, 2.0, 3.0, 4.0
    };
    const gfx::Matrix2 matrix_a{ matrix_values} ;
    const gfx::Matrix2 matrix_b{ matrix_a };

    for (int row = 0; row < 2; ++row)
        for (int col = 0; col < 2; ++col) {
            const float value = matrix_b[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 2 + col]);
        }
}

// Tests the assignment operator
TEST(GraphicsMatrix2, AssignmentOperator)
{
    std::array<const float, 4> matrix_values{
            1.0, 2.0, 3.0, 4.0,
    };
    const gfx::Matrix2 matrix_a{ matrix_values };
    gfx::Matrix2 matrix_b{ };

    matrix_b = matrix_a;

    for (int row = 0; row < 2; ++row)
        for (int col = 0; col < 2; ++col) {
            const float value = matrix_b[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 2 + col]);
        }
}


