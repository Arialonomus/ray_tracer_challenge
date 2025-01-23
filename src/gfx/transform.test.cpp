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
    const gfx::Matrix4 translate_matrix_float{ gfx::getTranslationMatrix(5.0, -3.0, 2.0) };

    ASSERT_TRUE(translate_matrix_float == translate_expected);

    const gfx::Vector4 translate_vector{ gfx::vector(5.0, -3.0, 2.0) };
    const gfx::Matrix4 translate_matrix_vector{ gfx::getTranslationMatrix(translate_vector) };

    ASSERT_TRUE(translate_matrix_vector == translate_expected);
}

// Tests translation of points and vectors by vector-matrix multiplication
TEST(GraphicsMatrixTransformations, Translation)
{
    const gfx::Matrix4 translate_matrix{ gfx::getTranslationMatrix(5.0, -3.0, 2.0) };
    const gfx::Vector4 point{ gfx::point(-3.0, 4.0, 5.0) };

    // Test basic point translation
    const gfx::Vector4 point_expected_a{ gfx::point(2.0, 1.0, 7.0) };
    const gfx::Vector4 point_actual_a{ translate_matrix * point };

    EXPECT_TRUE(point_actual_a == point_expected_a);

    // Test reverse translation via multiplying by translation matrix inverse
    const gfx::Vector4 point_expected_b{ gfx::point(-8.0, 7.0, 3.0) };
    const gfx::Vector4 point_actual_b{ translate_matrix.inverse() * point };

    EXPECT_TRUE(point_actual_b == point_expected_b);

    // Test that translation does not affect vectors
    const gfx::Vector4 vector{ gfx::vector(-3.0, 4.0, 5.0) };
    const gfx::Vector4 vector_translate_result{ translate_matrix * vector };

    EXPECT_TRUE(vector_translate_result == vector);

}