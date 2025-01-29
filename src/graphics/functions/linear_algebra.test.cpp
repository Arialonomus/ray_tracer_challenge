#include "gtest/gtest.h"
#include "linear_algebra.hpp"

// Tests generating a flattened 3x3 submatrix from a flattened 4x4 matrix
TEST(GraphicsLinearAlgebra, Submatrix4x4)
{
    const std::vector<double> matrix_vals{
        -6.0, 1.0, 1.0, 6.0,
        -8.0, 5.0, 8.0, 6.0,
        -1.0, 0.0, 8.0, 2.0,
        -7.0, 1.0, -1.0, 1.0
    };
    const std::vector<double> submatrix_vals_expected{
        -6.0, 1.0, 6.0,
        -8.0, 8.0, 6.0,
        -7.0, -1.0, 1.0
    };

    const std::vector<double> submatrix_vals_actual = gfx::getSubmatrix(matrix_vals, 2, 1);

    ASSERT_EQ(submatrix_vals_actual, submatrix_vals_expected);
}

// Tests generating a flattened 2x2 submatrix from a flattened 3x3 matrix
TEST(GraphicsLinearAlgebra, Submatrix3x3)
{
    const std::vector<double> matrix_vals{
            1.0, 5.0, 0.0,
            -3.0, 2.0, 7.0,
            0.0, 6.0, -3.0
    };
    const std::vector<double> submatrix_vals_expected{
            -3.0, 2.0,
            0.0, 6.0
    };

    const std::vector<double> submatrix_vals_actual = gfx::getSubmatrix(matrix_vals, 0, 2);

    ASSERT_EQ(submatrix_vals_actual, submatrix_vals_expected);
}

// Tests calculating the determinant of a flattened 2x2 matrix
TEST(GraphicsLinearAlgebra, Determinant2x2)
{
    const std::vector<double> matrix_a_vals{
            1.0, 5.0,
            -3.0, 2.0,
    };
    const double matrix_a_determinant_actual{ gfx::calculateDeterminant(matrix_a_vals) };
    const double matrix_a_determinant_expected{ 17 };

    EXPECT_FLOAT_EQ(matrix_a_determinant_actual, matrix_a_determinant_expected);
}

// Tests calculating the determinant of a flattened 3x3 matrix
TEST(GraphicsLinearAlgebra, Determinant3x3)
{
    const std::vector<double> matrix_a_vals{
            1.0, 2.0, 6.0,
            -5.0, 8.0, -4.0,
            2.0, 6.0, 4.0
    };
    const double matrix_a_determinant_actual{ gfx::calculateDeterminant(matrix_a_vals) };
    const double matrix_a_determinant_expected{ -196 };

    EXPECT_FLOAT_EQ(matrix_a_determinant_actual, matrix_a_determinant_expected);
}

// Tests calculating the determinant of a flattened 4x4 matrix
TEST(GraphicsLinearAlgebra, Determinant4x4)
{
    const std::vector<double> matrix_a_vals{
            -2.0, -8.0, 3.0, 5.0,
            -3.0, 1.0, 7.0, 3.0,
            1.0, 2.0, -9.0, 6.0,
            -6.0, 7.0, 7.0, -9.0
    };
    const double matrix_a_determinant_actual{ gfx::calculateDeterminant(matrix_a_vals) };
    const double matrix_a_determinant_expected{ -4071 };

    EXPECT_FLOAT_EQ(matrix_a_determinant_actual, matrix_a_determinant_expected);

    const std::vector<double> matrix_b_vals{
            6.0, 4.0, 4.0, 4.0,
            5.0, 5.0, 7.0, 6.0,
            4.0, -9.0, 3.0, -7.0,
            9.0, 1.0, 7.0, -6.0
    };
    const double matrix_b_determinant_actual{ gfx::calculateDeterminant(matrix_b_vals) };
    const double matrix_b_determinant_expected{ -2120 };

    EXPECT_FLOAT_EQ(matrix_b_determinant_actual, matrix_b_determinant_expected);

    const std::vector<double> matrix_c_vals{
            -4.0, 2.0, -2.0, -3.0,
            9.0, 6.0, 2.0, 6.0,
            0.0, -5.0, 1.0, -5.0,
            0.0, 0.0, 0.0, 0.0
    };
    const double matrix_c_determinant_actual{ gfx::calculateDeterminant(matrix_c_vals) };
    const double matrix_c_determinant_expected{ 0 };

    EXPECT_FLOAT_EQ(matrix_c_determinant_actual, matrix_c_determinant_expected);
}