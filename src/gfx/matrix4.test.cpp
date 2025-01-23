#include "gtest/gtest.h"

#include "matrix4.hpp"

// Tests the default constructor
TEST(GraphicsMatrix4, DefaultConstructor)
{
    const gfx::Matrix4 matrix;

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, 0.0);
        }
}

// Tests the float list constructor
TEST(GraphicsMatrix4, FloatListConstructor)
{
    std::array<const float, 16> matrix_values{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };
    const gfx::Matrix4 matrix{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 4 + col]);
        }
}

// Tests the span-based constructor
TEST(GraphicsMatrix4, SpanConstructor)
{
    std::array<const float, 16> matrix_values{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };
    const gfx::Matrix4 matrix{ matrix_values };

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            const float value = matrix[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 4 + col]);
        }
}

// Tests the copy constructor
TEST(GraphicsMatrix4, CopyConstructor)
{
    std::array<const float, 16> matrix_values{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };
    const gfx::Matrix4 matrix_a{ matrix_values} ;
    const gfx::Matrix4 matrix_b{ matrix_a };

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            const float value = matrix_b[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 4 + col]);
        }
}

// Tests the assignment operator
TEST(GraphicsMatrix4, AssignmentOperator)
{
    std::array<const float, 16> matrix_values{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };
    const gfx::Matrix4 matrix_a{ matrix_values };
    gfx::Matrix4 matrix_b{ };

    matrix_b = matrix_a;

    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            const float value = matrix_b[row, col];
            ASSERT_FLOAT_EQ(value, matrix_values[row * 4 + col]);
        }
}

// Tests the equality operator
TEST(GraphicsMatrix4, EqualityOperator)
{
    const gfx::Matrix4 matrix_a{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };
    const gfx::Matrix4 matrix_b{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0 };

    ASSERT_TRUE(matrix_a == matrix_b);
}

// Tests the inequality operator
TEST(GraphicsMatrix4, InequalityOperator)
{
    const gfx::Matrix4 matrix_a{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0
    };
    const gfx::Matrix4 matrix_b{ };

    ASSERT_TRUE(matrix_a != matrix_b);
}

// Tests matrix multiplication using the multiplication operator
TEST(GraphicsMatrix4, MatrixMultiplicationOperator)
{
    const gfx::Matrix4 matrix_a{
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 8.0, 7.0, 6.0,
            5.0, 4.0, 3.0, 2.0
    };
    const gfx::Matrix4 matrix_b{
            -2.0, 1.0, 2.0, 3.0,
            3.0, 2.0, 1.0, -1.0,
            4.0, 3.0, 6.0, 5.0,
            1.0, 2.0, 7.0, 8.0
    };
    const gfx::Matrix4 matrix_expected{
            20.0, 22.0, 50.0, 48.0,
            44.0, 54.0, 114.0, 108.0,
            40.0, 58.0, 110.0, 102.0,
            16.0, 26.0, 46.0, 42.0
    };

    const gfx::Matrix4 matrix_c = matrix_a * matrix_b;

    EXPECT_TRUE(matrix_c == matrix_expected);
}

// Tests matrix-vector multiplication using the multiplication operator
TEST(GraphicsMatrix4, VectorMultiplicationOperator)
{
    const gfx::Matrix4 matrix{
            1.0, 2.0, 3.0, 4.0,
            2.0, 4.0, 4.0, 2.0,
            8.0, 6.0, 4.0, 1.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Vector4 vector_a{ 1.0, 2.0, 3.0, 1.0 };
    const gfx::Vector4 vector_expected{ 18.0, 24.0, 33.0, 1.0 };

    const gfx::Vector4 vector_b = matrix * vector_a;

    EXPECT_TRUE(vector_b == vector_expected);
}

// Tests matrix-matrix and matrix-vector multiplication by the identity matrix
TEST(GraphicsMatrix4, IdentityMatrixMultiplication)
{
    const gfx::Matrix4 matrix_identity{
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 matrix_a{
            0.0, 1.0, 2.0, 4.0,
            1.0, 2.0, 4.0, 4.0,
            2.0, 4.0, 8.0, 16.0,
            4.0, 8.0, 16.0, 32.0
    };
    const gfx::Vector4 vector_a{ 1.0, 2.0, 3.0, 4.0 };

    const gfx::Matrix4 matrix_b = matrix_a * matrix_identity;

    EXPECT_TRUE(matrix_b == matrix_a);

    const gfx::Vector4 vector_b = matrix_identity * vector_a;

    EXPECT_TRUE(vector_b == vector_a);
}

// Tests matrix transposition
TEST(GraphicsMatrix4, Transpose)
{
    const gfx::Matrix4 matrix_initial{
            0.0, 9.0, 3.0, 0.0,
            9.0, 8.0, 0.0, 8.0,
            1.0, 8.0, 5.0, 3.0,
            0.0, 8.0, 3.0, 8.0
    };
    const gfx::Matrix4 matrix_expected{
            0.0, 9.0, 1.0, 0.0,
            9.0, 8.0, 8.0, 0.0,
            3.0, 0.0, 5.0, 5.0,
            0.0, 8.0, 3.0, 8.0
    };

    const gfx::Matrix4 matrix_transposed = matrix_initial.transpose();

    EXPECT_TRUE(matrix_transposed == matrix_expected);
}