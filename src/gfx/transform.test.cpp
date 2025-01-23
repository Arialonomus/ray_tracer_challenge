#include "gtest/gtest.h"
#include "transform.hpp"

#include "matrix4.hpp"
#include "vector4.hpp"

// Test creation of translation matrices
TEST(GraphicsMatrixTransformations, CreateTranslationMatrix)
{
    const gfx::Matrix4 translate_expected{
            1.0, 0.0, 0.0, 5.0,
            0.0, 1.0, 0.0, -3.0,
            0.0, 0.0, 1.0, 2.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 translate_matrix_float = gfx::getTranslationMatrix(5.0, -3.0, 2.0);

    ASSERT_TRUE(translate_matrix_float == translate_expected);

    const gfx::Vector4 translate_vector = gfx::vector(5.0, -3.0, 2.0);
    const gfx::Matrix4 translate_matrix_vector = gfx::getTranslationMatrix(translate_vector);

    ASSERT_TRUE(translate_matrix_vector == translate_expected);
}