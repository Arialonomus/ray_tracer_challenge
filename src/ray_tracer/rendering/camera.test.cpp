#include "gtest/gtest.h"
#include "camera.hpp"

#include <cmath>

#include "matrix4.hpp"
#include "vector4.hpp"
#include "transform.hpp"
#include "ray.hpp"

// Tests the standard constructor (no transform)
TEST(RayTracerCamera, StandardConstructorNoTransform)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const double field_of_view_expected{ M_PI_2 };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    const rt::Camera camera{ viewport_width_expected,
                              viewport_height_expected,
                              field_of_view_expected };

    ASSERT_EQ(camera.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera.getTransform(), transform_expected);
}

// Tests the standard constructor
TEST(RayTracerCamera, StandardConstructor)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const double field_of_view_expected{ M_PI_2 };

    const gfx::Vector4 from_position{ gfx::createPoint(0, 0, 8) };
    const gfx::Vector4 to_position{ gfx::createPoint(0, 0, 0) };
    const gfx::Vector4 up_vector{ gfx::createVector(0, 1, 0) };
    const gfx::Matrix4 transform_expected{
            gfx::createViewTransformMatrix(
                    from_position,
                    to_position,
                    up_vector) };

    const rt::Camera camera{ viewport_width_expected,
                              viewport_height_expected,
                              field_of_view_expected,
                              transform_expected};


    ASSERT_EQ(camera.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera.getTransform(), transform_expected);
}

// Tests the copy constructor
TEST(RayTracerCamera, CopyConstructor)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const double field_of_view_expected{ M_PI_2 };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    const rt::Camera camera_src{ viewport_width_expected,
                                  viewport_height_expected,
                                  field_of_view_expected };

    const rt::Camera camera_cpy{ camera_src };

    ASSERT_EQ(camera_cpy.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera_cpy.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera_cpy.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera_cpy.getTransform(), transform_expected);
}

// Tests the assignment operator
TEST(RayTracerCamera, AssignmentOperator)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const double field_of_view_expected{ M_PI_2 };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    const rt::Camera camera_a{ viewport_width_expected,
                                  viewport_height_expected,
                                  field_of_view_expected };

    rt::Camera camera_b{ 100, 100, 0 };
    camera_b = camera_a;

    ASSERT_EQ(camera_b.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera_b.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera_b.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera_b.getTransform(), transform_expected);
}

// Tests the equality operator
TEST(RayTracerCamera, EqualityOperator)
{
    const rt::Camera camera_a{ 160, 120, M_PI_2 };
    const rt::Camera camera_b{ 160, 120, M_PI_2 };

    ASSERT_TRUE(camera_a == camera_b);
}

// Tests the inequality operator
TEST(RayTracerCamera, InequalityOperator)
{
    const rt::Camera camera_a{ 160, 120, M_PI_2 };
    const rt::Camera camera_b{ 100, 100, 0 };

    ASSERT_TRUE(camera_a != camera_b);
}

// Tests mutator methods
TEST(RayTracerCamera, Mutators)
{
    rt::Camera camera{ 160, 120, M_PI_2 };

    // Test setViewport()
    const size_t viewport_width_expected_a{ 100 };
    const size_t viewport_height_expected_a{ 100 };
    camera.setViewport(viewport_width_expected_a, viewport_height_expected_a);
    ASSERT_FLOAT_EQ(camera.getViewportWidth(), viewport_width_expected_a);
    ASSERT_FLOAT_EQ(camera.getViewportHeight(), viewport_height_expected_a);

    // Test setViewportWidth()
    const size_t viewport_width_expected_b{ 500 };
    camera.setViewportWidth(viewport_width_expected_b);
    ASSERT_EQ(camera.getViewportWidth(), viewport_width_expected_b);

    // Test setViewportHeight()
    const size_t viewport_height_expected_b{ 550 };
    camera.setViewportHeight(viewport_height_expected_b);
    ASSERT_EQ(camera.getViewportHeight(), viewport_height_expected_b);

    // Test setFieldOfView()
    const double field_of_view_expected{ M_PI_4 };
    camera.setFieldOfView(field_of_view_expected);
    ASSERT_FLOAT_EQ(camera.getFieldOfView(), field_of_view_expected);

    // Test setTransform()
    const gfx::Vector4 from_position{ gfx::createPoint(0, 0, 8) };
    const gfx::Vector4 to_position{ gfx::createPoint(0, 0, 0) };
    const gfx::Vector4 up_vector{ gfx::createVector(0, 1, 0) };
    const gfx::Matrix4 transform_expected{
            gfx::createViewTransformMatrix(
                    from_position,
                    to_position,
                    up_vector) };
    camera.setTransform(transform_expected);
    ASSERT_EQ(camera.getTransform(), transform_expected);
}

// Tests casting a ray through various positions on the viewport
TEST(RayTracerCamera, CastRay)
{
    const rt::Camera camera_a{ 201, 101, M_PI_2 };

    // Test casting a ray through the center of the viewport
    const gfx::Ray ray_a_expected{ 0, 0, 0,
                                   0, 0, -1 };
    const gfx::Ray ray_a_actual{ camera_a.castRay(100, 50) };

    EXPECT_EQ(ray_a_actual, ray_a_expected);

    // Test casting a ray through a corner of the viewport
    const gfx::Ray ray_b_expected{ 0, 0, 0,
                                   0.665186, 0.332593, -0.668512 };
    const gfx::Ray ray_b_actual{ camera_a.castRay(0, 0) };

    EXPECT_EQ(ray_b_actual, ray_b_expected);

    // Test casting a ray from a transformed camera through the center of the viewport
    const gfx::Matrix4 transform_matrix{
        gfx::createYRotationMatrix(M_PI_4) * gfx::createTranslationMatrix(0, -2, 5) };
    const rt::Camera camera_b{ 201, 101, M_PI_2, transform_matrix };
    const gfx::Ray ray_c_expected{ 0, 2, -5,
                                   M_SQRT2 / 2, 0, -M_SQRT2 / 2 };
    const gfx::Ray ray_c_actual{ camera_b.castRay(100, 50) };

    EXPECT_EQ(ray_c_actual, ray_c_expected);
}