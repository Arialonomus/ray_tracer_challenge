#include "gtest/gtest.h"
#include "linear_algebra.hpp"

// Tests generating a flattened 3x3 submatrix from a flattened 4x4 matrix
TEST(GraphicsLinearAlgebra, Submatrix4x4)
{
    const std::vector<float> matrix_vals{
        -6.0, 1.0, 1.0, 6.0,
        -8.0, 5.0, 8.0, 6.0,
        -1.0, 0.0, 8.0, 2.0,
        -7.0, 1.0, -1.0, 1.0
    };
    const std::vector<float> submatrix_vals_expected{
        -6.0, 1.0, 6.0,
        -8.0, 8.0, 6.0,
        -7.0, -1.0, 1.0
    };

    const std::vector<float> submatrix_vals_actual = gfx::submatrix(matrix_vals, 2, 1);

    ASSERT_EQ(submatrix_vals_actual, submatrix_vals_expected);
}

// Tests generating a flattened 2x2 submatrix from a flattened 3x3 matrix
TEST(GraphicsLinearAlgebra, Submatrix3x3)
{
    const std::vector<float> matrix_vals{
            1.0, 5.0, 0.0,
            -3.0, 2.0, 7.0,
            0.0, 6.0, -3.0
    };
    const std::vector<float> submatrix_vals_expected{
            -3.0, 2.0,
            0.0, 6.0
    };

    const std::vector<float> submatrix_vals_actual = gfx::submatrix(matrix_vals, 0, 2);

    ASSERT_EQ(submatrix_vals_actual, submatrix_vals_expected);
}