#include "gtest/gtest.h"
#include "matrix3.hpp"

#include "vector3.hpp"

// Tests the default constructor
TEST(GraphicsMatrix3, DefaultConstructor)
{
    const gfx::Matrix3 matrix;
    const gfx::Matrix3 identity_matrix{
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
    };
    EXPECT_EQ(matrix, identity_matrix);
}

// Tests the float list constructor
TEST(GraphicsMatrix3, FloatListConstructor)
{
    std::array<const double, 9> matrix_values{
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
            const double value = matrix[row, col];
            EXPECT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the span-based constructor
TEST(GraphicsMatrix3, SpanConstructor)
{
    std::array<const double, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix{ matrix_values };

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const double value = matrix[row, col];
            EXPECT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the copy constructor
TEST(GraphicsMatrix3, CopyConstructor)
{
    std::array<const double, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_a{ matrix_values } ;
    const gfx::Matrix3 matrix_b{ matrix_a };

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const double value = matrix_b[row, col];
            EXPECT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
        }
}

// Tests the assignment operator
TEST(GraphicsMatrix3, AssignmentOperator)
{
    std::array<const double, 9> matrix_values{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_a{ matrix_values };
    gfx::Matrix3 matrix_b{ };

    matrix_b = matrix_a;

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col) {
            const double value = matrix_b[row, col];
            EXPECT_FLOAT_EQ(value, matrix_values[row * 3 + col]);
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

    EXPECT_TRUE(matrix_a == matrix_b);
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

    EXPECT_TRUE(matrix_a != matrix_b);
}


// Tests the isIdentityMatrix function
TEST(GraphicsMatrix3, IsIdentityMatrix)
{
    const gfx::Matrix3 matrix_default{ };
    EXPECT_TRUE(matrix_default.isIdentityMatrix());

    const gfx::Matrix3 matrix_custom{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0,
    };
    EXPECT_FALSE(matrix_custom.isIdentityMatrix());
}

// Tests matrix multiplication using the multiplication operator
TEST(GraphicsMatrix3, MatrixMultiplicationOperator)
{
    const gfx::Matrix3 matrix_a{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_b{
            -2.0, 1.0, 2.0,
            3.0, 3.0, 2.0,
            1.0, -1.0, 4.0
    };
    const gfx::Matrix3 matrix_expected{
            7.0, 4.0, 18.0,
            13.0, 13.0, 42.0,
            19.0, 22.0, 66.0
    };

    const gfx::Matrix3 matrix_c = matrix_a * matrix_b;

    EXPECT_TRUE(matrix_c == matrix_expected);
}

// Tests matrix multiplication with the multiplication shorthand operator
TEST(GraphicsMatrix3, MatrixMultiplicationShorthandOperator)
{
    gfx::Matrix3 matrix_a{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
    };
    const gfx::Matrix3 matrix_b{
            -2.0, 1.0, 2.0,
            3.0, 3.0, 2.0,
            1.0, -1.0, 4.0
    };
    const gfx::Matrix3 matrix_expected{
            7.0, 4.0, 18.0,
            13.0, 13.0, 42.0,
            19.0, 22.0, 66.0
    };

    matrix_a *= matrix_b;

    EXPECT_TRUE(matrix_a == matrix_expected);
}

// Tests matrix-matrix and matrix-vector multiplication by the identity matrix
TEST(GraphicsMatrix3, IdentityMatrixMultiplication)
{
    const gfx::Matrix3 matrix_identity{ };
    const gfx::Matrix3 matrix_a{
            0.0, 1.0, 2.0,
            1.0, 2.0, 4.0,
            2.0, 4.0, 8.0
    };
    const gfx::Vector3 vector_a{ 1.0, 2.0, 3.0 };

    const gfx::Matrix3 matrix_b = matrix_a * matrix_identity;
    EXPECT_TRUE(matrix_b == matrix_a);

    const gfx::Vector3 vector_b = matrix_identity * vector_a;
    EXPECT_TRUE(vector_b == vector_a);
}

// Tests matrix transposition
TEST(GraphicsMatrix3, Transpose)
{
    const gfx::Matrix3 matrix_initial{
            0.0, 9.0, 3.0,
            9.0, 8.0, 0.0,
            1.0, 8.0, 5.0
    };
    const gfx::Matrix3 matrix_expected{
            0.0, 9.0, 1.0,
            9.0, 8.0, 8.0,
            3.0, 0.0, 5.0
    };

    const gfx::Matrix3 matrix_transposed = matrix_initial.transpose();
    EXPECT_TRUE(matrix_transposed == matrix_expected);
}

// Tests matrix inversion
TEST(GraphicsMatrix3, InvertMatrix)
{
    const gfx::Matrix3 matrix{
            1, 2, -1,
            2, 1, 2,
            -1, 2, 1
    };
    const gfx::Matrix3 matrix_inverse_expected{
            0.1875, 0.25, -0.3125,
            0.25, 0, 0.25,
            -0.3125, 0.25, 0.1875
    };

    const gfx::Matrix3 matrix_a_inverse_actual = matrix.inverse();
    EXPECT_TRUE(matrix_a_inverse_actual == matrix_inverse_expected);
}

// Tests inversion of the identity matrix
TEST(GraphicsMatrix3, InvertIdentityMatrix)
{
    const gfx::Matrix3 matrix_identity{ };
    const gfx::Matrix3 matrix_inverse{ matrix_identity.inverse() };

    EXPECT_EQ(matrix_inverse, matrix_identity);
}

// Tests multiplying a matrix by its inverse to get the identity matrix
TEST(GraphicsMatrix3, MultiplyByInverse)
{
    const gfx::Matrix3 matrix_a{
            8.0, -5.0, 9.0,
            7.0, 5.0, 6.0,
            -6.0, 0.0, 9.0
    };
    const gfx::Matrix3 matrix_identity{
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
    };

    const gfx::Matrix3 matrix_b = matrix_a * matrix_a.inverse();

    EXPECT_TRUE(matrix_b == matrix_identity);
}

// Tests multiplying a matrix product by a matrix inverse to get one of the factor matrices back
TEST(GraphicsMatrix3, MultiplyProductByFactorInverse)
{
    const gfx::Matrix3 matrix_a{
            3.0, -9.0, 7.0,
            3.0, -8.0, 2.0,
            -4.0, 4.0, 4.0
    };
    const gfx::Matrix3 matrix_b{
            8.0, 2.0, 2.0,
            3.0, -1.0, 7.0,
            7.0, 0.0, 5.0
    };

    const gfx::Matrix3 matrix_c = matrix_a * matrix_b;
    const gfx::Matrix3 matrix_d = matrix_c * matrix_b.inverse();

    EXPECT_TRUE(matrix_d == matrix_a);
}