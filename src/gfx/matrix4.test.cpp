#include "gtest/gtest.h"
#include "matrix4.hpp"

#include "matrix3.hpp"
#include "vector4.hpp"

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

// Tests the identity matrix factory function
TEST(GraphicsMatrix4, CreateIdentityMatrix)
{
    const gfx::Matrix4 matrix_expected{
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 matrix_actual{ gfx::createIdentityMatrix() };

    ASSERT_TRUE(matrix_actual == matrix_expected);
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

// Tests matrix-matrix and matrix-vector multiplication by the identity matrix
TEST(GraphicsMatrix4, IdentityMatrixMultiplication)
{
    const gfx::Matrix4 matrix_identity{ gfx::createIdentityMatrix() };
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
            0.0, 0.0, 5.0, 8.0
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

// Tests generating 3x3 submatrix
TEST(GraphicsMatrix4, Submatrix)
{
    const gfx::Matrix4 matrix{
            -6.0, 1.0, 1.0, 6.0,
            -8.0, 5.0, 8.0, 6.0,
            -1.0, 0.0, 8.0, 2.0,
            -7.0, 1.0, -1.0, 1.0
    };
    const gfx::Matrix3 submatrix_expected{
            -6.0, 1.0, 6.0,
            -8.0, 8.0, 6.0,
            -7.0, -1.0, 1.0
    };

    const gfx::Matrix3 submatrix_actual = matrix.submatrix(2, 1);

    EXPECT_TRUE(submatrix_actual == submatrix_expected);
}

// Tests calculating the determinant of a 4x4 matrix
TEST(GraphicsMatrix4, Determinant)
{
    const gfx::Matrix4 matrix_a{
            -2.0, -8.0, 3.0, 5.0,
            -3.0, 1.0, 7.0, 3.0,
            1.0, 2.0, -9.0, 6.0,
            -6.0, 7.0, 7.0, -9.0
    };

    EXPECT_FLOAT_EQ(matrix_a.determinant(), -4071.0);

    const gfx::Matrix4 matrix_b{
            6.0, 4.0, 4.0, 4.0,
            5.0, 5.0, 7.0, 6.0,
            4.0, -9.0, 3.0, -7.0,
            9.0, 1.0, 7.0, -6.0
    };

    EXPECT_FLOAT_EQ(matrix_b.determinant(), -2120.0);

    const gfx::Matrix4 matrix_c{
            -4.0, 2.0, -2.0, -3.0,
            9.0, 6.0, 2.0, 6.0,
            0.0, -5.0, 1.0, -5.0,
            0.0, 0.0, 0.0, 0.0
    };

    EXPECT_FLOAT_EQ(matrix_c.determinant(), 0.0);
}

// Tests matrix inversion
TEST(GraphicsMatrix4, InvertMatrix)
{
    const gfx::Matrix4 matrix_a{
            -5.0, 2.0, 6.0, -8.0,
            1.0, -5.0, 1.0, 8.0,
            7.0, 7.0, -6.0, -7.0,
            1.0, -3.0, 7.0, 4.0
    };
    const gfx::Matrix4 matrix_a_inverse_expected{
            0.218045115, 0.451127827, 0.24060151, -0.0451127812,
            -0.808270693, -1.45676696, -0.443609029, 0.520676672,
            -0.0789473653, -0.223684207, -0.0526315793, 0.197368428,
            -0.522556365, -0.813909769, -0.300751865, 0.306390971
    };

    const gfx::Matrix4 matrix_a_inverse_actual = matrix_a.inverse();

    EXPECT_TRUE(matrix_a_inverse_actual == matrix_a_inverse_expected);

    const gfx::Matrix4 matrix_b{
            8.0, -5.0, 9.0, 2.0,
            7.0, 5.0, 6.0, 1.0,
            -6.0, 0.0, 9.0, 6.0,
            -3.0, 0.0, -9.0, -4.0
    };
    const gfx::Matrix4 matrix_b_inverse_expected{
            -0.15384616, -0.15384616, -0.282051295, -0.538461566,
            -0.0769230798, 0.123076923, 0.025641026, 0.0307692308,
            0.358974367, 0.358974367, 0.43589744, 0.923076928,
            -0.692307711, -0.692307711, -0.769230783, -1.92307687
    };

    const gfx::Matrix4 matrix_b_inverse_actual = matrix_b.inverse();

    EXPECT_TRUE(matrix_b_inverse_actual == matrix_b_inverse_expected);

    const gfx::Matrix4 matrix_c{
            9.0, 3.0, 0.0, 9.0,
            -5.0, -2.0, -6.0, -3.0,
            -4.0, 9.0, 6.0, 4.0,
            -7.0, 6.0, 6.0, 2.0
    };
    const gfx::Matrix4 matrix_c_inverse_expected{
            -0.0407407396, -0.0777777806, 0.144444451, -0.222222224,
            -0.0777777806, 0.0333333351, 0.366666675, -0.333333343,
            -0.0290123448, -0.146296293, -0.109259263, 0.129629627,
            0.177777782, 0.0666666701, -0.266666681, 0.333333343
    };

    const gfx::Matrix4 matrix_c_inverse_actual = matrix_c.inverse();

    EXPECT_TRUE(matrix_c_inverse_actual == matrix_c_inverse_expected);
}

// Tests multiplying a matrix by its inverse to get the identity matrix
TEST(GraphicsMatrix4, MultiplyByInverse)
{
    const gfx::Matrix4 matrix_a{
            8.0, -5.0, 9.0, 2.0,
            7.0, 5.0, 6.0, 1.0,
            -6.0, 0.0, 9.0, 6.0,
            -3.0, 0.0, -9.0, -4.0
    };
    const gfx::Matrix4 matrix_identity{
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };

    const gfx::Matrix4 matrix_b = matrix_a * matrix_a.inverse();

    EXPECT_TRUE(matrix_b == matrix_identity);
}

// Tests multiplying a matrix product by a matrix inverse to get one of the factor matrices back
TEST(GraphicsMatrix4, MultiplyProductByFactorInverse)
{
    const gfx::Matrix4 matrix_a{
            3.0, -9.0, 7.0, 3.0,
            3.0, -8.0, 2.0, -9.0,
            -4.0, 4.0, 4.0, 1.0,
            -6.0, 5.0, -1.0, 1.0
    };
    const gfx::Matrix4 matrix_b{
            8.0, 2.0, 2.0, 2.0,
            3.0, -1.0, 7.0, 0.0,
            7.0, 0.0, 5.0, 4.0,
            6.0, -2.0, 0.0, 5.0
    };

    const gfx::Matrix4 matrix_c = matrix_a * matrix_b;
    const gfx::Matrix4 matrix_d = matrix_c * matrix_b.inverse();

    EXPECT_TRUE(matrix_d == matrix_a);
}