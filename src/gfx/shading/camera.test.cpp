#include "gtest/gtest.h"
#include "camera.hpp"

#include <cmath>

#include "matrix4.hpp"
#include "vector4.hpp"
#include "transform.hpp"
#include "ray.hpp"

// Tests the standard constructor (no transform)
TEST(GraphicsCamera, StandardConstructorNoTransform)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const float field_of_view_expected{ M_PI_2f };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    const gfx::Camera camera{ viewport_width_expected,
                              viewport_height_expected,
                              field_of_view_expected };

    ASSERT_EQ(camera.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera.getTransform(), transform_expected);
}

// Tests the standard constructor
TEST(GraphicsCamera, StandardConstructor)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const float field_of_view_expected{ M_PI_2f };

    const gfx::Vector4 from_position{ gfx::createPoint(0, 0, 8) };
    const gfx::Vector4 to_position{ gfx::createPoint(0, 0, 0) };
    const gfx::Vector4 up_vector{ gfx::createVector(0, 1, 0) };
    const gfx::Matrix4 transform_expected{
            gfx::createViewTransformMatrix(
                    from_position,
                    to_position,
                    up_vector) };

    const gfx::Camera camera{ viewport_width_expected,
                              viewport_height_expected,
                              field_of_view_expected,
                              transform_expected};


    ASSERT_EQ(camera.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera.getTransform(), transform_expected);
}

// Tests the copy constructor
TEST(GraphicsCamera, CopyConstructor)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const float field_of_view_expected{ M_PI_2f };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    const gfx::Camera camera_src{ viewport_width_expected,
                                  viewport_height_expected,
                                  field_of_view_expected };

    const gfx::Camera camera_cpy{ camera_src };

    ASSERT_EQ(camera_cpy.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera_cpy.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera_cpy.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera_cpy.getTransform(), transform_expected);
}

// Tests the assignment operator
TEST(GraphicsCamera, AssignmentOperator)
{
    const size_t viewport_width_expected{ 160 };
    const size_t viewport_height_expected{ 120 };
    const float field_of_view_expected{ M_PI_2f };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    const gfx::Camera camera_a{ viewport_width_expected,
                                  viewport_height_expected,
                                  field_of_view_expected };

    gfx::Camera camera_b{ 100, 100, 0 };
    camera_b = camera_a;

    ASSERT_EQ(camera_b.getViewportWidth(), viewport_width_expected);
    ASSERT_EQ(camera_b.getViewportHeight(), viewport_height_expected);
    ASSERT_FLOAT_EQ(camera_b.getFieldOfView(), field_of_view_expected);
    ASSERT_EQ(camera_b.getTransform(), transform_expected);
}

// Tests the equality operator
TEST(GraphicsCamera, EqualityOperator)
{
    const gfx::Camera camera_a{ 160, 120, M_PI_2f };
    const gfx::Camera camera_b{ 160, 120, M_PI_2f };

    ASSERT_TRUE(camera_a == camera_b);
}

// Tests the inequality operator
TEST(GraphicsCamera, InequalityOperator)
{
    const gfx::Camera camera_a{ 160, 120, M_PI_2f };
    const gfx::Camera camera_b{ 100, 100, 0 };

    ASSERT_TRUE(camera_a != camera_b);
}

// Tests mutator methods
TEST(GraphicsCamera, Mutators)
{
    gfx::Camera camera{ 160, 120, M_PI_2f };

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
    const float field_of_view_expected{ M_PI_4f };
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
