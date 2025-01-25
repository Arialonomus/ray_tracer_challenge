#include "gtest/gtest.h"
#include "sphere.hpp"

#include "transform.hpp"

// Tests the default constructor
TEST(GraphicsSphere, DefaultConstructor)
{
    const gfx::Sphere sphere{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(sphere.getTransform(), transform_expected);
}

// Tests the standard constructor
TEST(GraphicsSphere, StandardConstructor)
{
    const gfx::Sphere sphere{ gfx::createScalingMatrix(5) };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    ASSERT_EQ(sphere.getTransform(), transform_expected);
}

// Tests the copy constructor
TEST(GraphicsSphere, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_src{ transform_expected };
    const gfx::Sphere sphere_cpy{ sphere_src };

    ASSERT_EQ(sphere_cpy.getTransform(), transform_expected);
}

// Tests the assignment operator
TEST(GraphicsSphere, AssignmentOperator)
{

    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ transform_expected };
    gfx::Sphere sphere_b{ };

    sphere_b = sphere_a;

    ASSERT_EQ(sphere_b.getTransform(), transform_expected);
}

// Tests the equality operator
TEST(GraphicsSphere, EqualityOperator)
{
    const gfx::Sphere sphere_a{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_b{ gfx::createScalingMatrix(5) };

    ASSERT_TRUE(sphere_a == sphere_b);
}

// Tests the inequality operator
TEST(GraphicsSphere, InequalityOperator)
{
    const gfx::Sphere sphere_a{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_b{ };

    ASSERT_TRUE(sphere_a != sphere_b);
}

// Test setting the transform of a sphere
TEST(GraphicsSphere, SetTransform)
{
    gfx::Sphere sphere{ };
    const gfx::Matrix4 translate_matrix{ gfx::createTranslationMatrix(2, 3, 4) };

    sphere.setTransform(translate_matrix);

    ASSERT_EQ(sphere.getTransform(), translate_matrix);
}