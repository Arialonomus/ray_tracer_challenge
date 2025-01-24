#include "gtest/gtest.h"
#include "transform.hpp"

#include <cmath>

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
    const gfx::Matrix4 translate_matrix_float{ gfx::createTranslationMatrix(5.0, -3.0, 2.0) };

    ASSERT_TRUE(translate_matrix_float == translate_expected);

    const gfx::Vector4 translate_vector{ gfx::createVector(5.0, -3.0, 2.0) };
    const gfx::Matrix4 translate_matrix_vector{ gfx::createTranslationMatrix(translate_vector) };

    ASSERT_TRUE(translate_matrix_vector == translate_expected);
}

// Tests translation of points and vectors by vector-matrix multiplication
TEST(GraphicsMatrixTransformations, Translation)
{
    const gfx::Matrix4 translate_matrix{ gfx::createTranslationMatrix(5.0, -3.0, 2.0) };
    const gfx::Vector4 point{ gfx::createPoint(-3.0, 4.0, 5.0) };

    // Test basic point translation
    const gfx::Vector4 point_expected_a{ gfx::createPoint(2.0, 1.0, 7.0) };
    const gfx::Vector4 point_actual_a{ translate_matrix * point };

    EXPECT_TRUE(point_actual_a == point_expected_a);

    // Test reverse translation via multiplying by translation matrix inverse
    const gfx::Vector4 point_expected_b{ gfx::createPoint(-8.0, 7.0, 3.0) };
    const gfx::Vector4 point_actual_b{ translate_matrix.inverse() * point };

    EXPECT_TRUE(point_actual_b == point_expected_b);

    // Test that translation does not affect vectors
    const gfx::Vector4 vector{ gfx::createVector(-3.0, 4.0, 5.0) };
    const gfx::Vector4 vector_translate_result{ translate_matrix * vector };

    EXPECT_TRUE(vector_translate_result == vector);
}

// Test creation of translation matrices
TEST(GraphicsMatrixTransformations, CreateScalingMatrix)
{
    const gfx::Matrix4 scale_expected{
            2.0, 0.0, 0.0, 0.0,
            0.0, 3.0, 0.0, 0.0,
            0.0, 0.0, 4.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 scale_matrix_float{ gfx::createScalingMatrix(2.0, 3.0, 4.0) };

    ASSERT_TRUE(scale_matrix_float == scale_expected);

    const gfx::Vector4 scale_vector{ gfx::createVector(2.0, 3.0, 4.0) };
    const gfx::Matrix4 scale_matrix_vector{ gfx::createScalingMatrix(scale_vector) };

    ASSERT_TRUE(scale_matrix_vector == scale_expected);
}


// Tests scaling of points and vectors by vector-matrix multiplication
TEST(GraphicsMatrixTransformations, Scaling)
{
    const gfx::Matrix4 scale_matrix{ gfx::createScalingMatrix(2.0, 3.0, 4.0) };
    const gfx::Vector4 point_initial{ gfx::createPoint(-4.0, 6.0, 8.0) };

    // Test scaling a point
    const gfx::Vector4 point_expected{ gfx::createPoint(-8.0, 18.0, 32.0) };
    const gfx::Vector4 point_scaled_actual{ scale_matrix * point_initial };

    EXPECT_TRUE(point_scaled_actual == point_expected);

    // Test scaling a vector
    const gfx::Vector4 vector_initial{ gfx::createVector(-4.0, 6.0, 8.0) };
    const gfx::Vector4 vector_expected_a{ gfx::createVector(-8.0, 18.0, 32.0) };
    const gfx::Vector4 vector_scaled_actual_a{ scale_matrix * vector_initial };

    EXPECT_TRUE(vector_scaled_actual_a == vector_expected_a);

    // Test reverse scaling of a vector via multiplying by scaling matrix inverse
    const gfx::Vector4 vector_expected_b{ gfx::createVector(-2.0, 2.0, 2.0) };
    const gfx::Vector4 vector_scaled_actual_b{ scale_matrix.inverse() * vector_initial };

    EXPECT_TRUE(vector_scaled_actual_b == vector_expected_b);
}

// Tests reflection of a point by vector-matrix multiplication using negative scaling matrix values
TEST(GraphicsMatrixTransformations, Reflection)
{
    const gfx::Matrix4 reflection_matrix{ gfx::createScalingMatrix(-1.0, 1.0, 1.0) };
    const gfx::Vector4 point_initial{ gfx::createPoint(2.0, 3.0, 4.0) };

    const gfx::Vector4 point_expected{ gfx::createPoint(-2.0, 3.0, 4.0) };
    const gfx::Vector4 point_reflected_actual{ reflection_matrix * point_initial };

    EXPECT_TRUE(point_reflected_actual == point_expected);
}

// Test creation of rotation matrices
TEST(GraphicsMatrixTransformations, CreateRotationMatrices)
{
    // Test creation of x-axis rotation matrix
    const gfx::Matrix4 x_rotation_matrix_expected{
            1.0, 0.0, 0.0, 0.0,
            0.0, std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f, 0.0,
            0.0, std::sqrt(2.0f) / 2.0f, std::sqrt(2.0f) / 2.0f, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 x_rotation_matrix_actual{ gfx::createXRotationMatrix(M_PI_4) };

    ASSERT_TRUE(x_rotation_matrix_actual == x_rotation_matrix_expected);

    // Test creation of y-axis rotation matrix
    const gfx::Matrix4 y_rotation_matrix_expected{
            std::sqrt(2.0f) / 2.0f, 0.0, std::sqrt(2.0f) / 2.0f, 0.0,
            0.0, 1.0, 0.0, 0.0,
            -std::sqrt(2.0f) / 2.0f, 0.0, std::sqrt(2.0f) / 2.0f, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 y_rotation_matrix_actual{ gfx::createYRotationMatrix(M_PI_4) };

    ASSERT_TRUE(y_rotation_matrix_actual == y_rotation_matrix_expected);

    // Test creation of z-axis rotation matrix
    const gfx::Matrix4 z_rotation_matrix_expected{
            std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f, 0.0, 0.0,
            std::sqrt(2.0f) / 2.0f, std::sqrt(2.0f) / 2.0f, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    const gfx::Matrix4 z_rotation_matrix_actual{ gfx::createZRotationMatrix(M_PI_4) };

    ASSERT_TRUE(z_rotation_matrix_actual == z_rotation_matrix_expected);
}

// Tests rotating points around the x-axis
TEST(GraphicsMatrixTransformations, XAxisRotation)
{
    const gfx::Vector4 point_initial{ gfx::createPoint(0.0, 1.0, 0.0) };
    const gfx::Matrix4 x_rotation_matrix_half_quarter{ gfx::createXRotationMatrix(M_PI_4) };
    const gfx::Matrix4 x_rotation_matrix_full_quarter{ gfx::createXRotationMatrix(M_PI_2) };

    const gfx::Vector4 point_half_quarter_expected{ gfx::createPoint(0.0,
                                                                     std::sqrt(2.0f) / 2.0f,
                                                                     std::sqrt(2.0f) / 2.0f) };
    const gfx::Vector4 point_half_quarter_actual{ x_rotation_matrix_half_quarter * point_initial  };

    EXPECT_TRUE(point_half_quarter_actual == point_half_quarter_expected);

    const gfx::Vector4 point_full_quarter_expected{ gfx::createPoint(0.0, 0.0, 1.0) };
    const gfx::Vector4 point_full_quarter_actual{ x_rotation_matrix_full_quarter * point_initial  };

    EXPECT_TRUE(point_full_quarter_actual == point_full_quarter_expected);
}

// Tests rotating points around the y-axis
TEST(GraphicsMatrixTransformations, YAxisRotation)
{
    const gfx::Vector4 point_initial{ gfx::createPoint(0.0, 0.0, 1.0) };
    const gfx::Matrix4 y_rotation_matrix_half_quarter{ gfx::createYRotationMatrix(M_PI_4) };
    const gfx::Matrix4 y_rotation_matrix_full_quarter{ gfx::createYRotationMatrix(M_PI_2) };

    const gfx::Vector4 point_half_quarter_expected{ gfx::createPoint(std::sqrt(2.0f) / 2.0f,
                                                                     0.0,
                                                                     std::sqrt(2.0f) / 2.0f) };
    const gfx::Vector4 point_half_quarter_actual{ y_rotation_matrix_half_quarter * point_initial  };

    EXPECT_TRUE(point_half_quarter_actual == point_half_quarter_expected);

    const gfx::Vector4 point_full_quarter_expected{ gfx::createPoint(1.0, 0.0, 0.0) };
    const gfx::Vector4 point_full_quarter_actual{ y_rotation_matrix_full_quarter * point_initial  };

    EXPECT_TRUE(point_full_quarter_actual == point_full_quarter_expected);
}

// Tests rotating points around the z-axis
TEST(GraphicsMatrixTransformations, ZAxisRotation)
{
    const gfx::Vector4 point_initial{ gfx::createPoint(0.0, 1.0, 0.0) };
    const gfx::Matrix4 z_rotation_matrix_half_quarter{ gfx::createZRotationMatrix(M_PI_4) };
    const gfx::Matrix4 z_rotation_matrix_full_quarter{ gfx::createZRotationMatrix(M_PI_2) };

    const gfx::Vector4 point_half_quarter_expected{ gfx::createPoint(-std::sqrt(2.0f) / 2.0f,
                                                                     std::sqrt(2.0f) / 2.0f,
                                                                     0.0) };
    const gfx::Vector4 point_half_quarter_actual{ z_rotation_matrix_half_quarter * point_initial  };

    EXPECT_TRUE(point_half_quarter_actual == point_half_quarter_expected);

    const gfx::Vector4 point_full_quarter_expected{ gfx::createPoint(-1.0, 0.0, 0.0) };
    const gfx::Vector4 point_full_quarter_actual{ z_rotation_matrix_full_quarter * point_initial  };

    EXPECT_TRUE(point_full_quarter_actual == point_full_quarter_expected);
}