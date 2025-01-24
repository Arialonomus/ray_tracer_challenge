#include "gtest/gtest.h"
#include "ray.hpp"

#include "vector4.hpp"

// Tests the default constructor
TEST(GraphicsRay, DefaultConstructor)
{
    const gfx::Ray ray;
    const gfx::Vector4 origin_expected{ 0.0, 0.0, 0.0, 1.0 };
    const gfx::Vector4 direction_expected{ 0.0, 0.0, 0.0, 0.0 };

    ASSERT_EQ(ray.getOrigin(), origin_expected);
    ASSERT_EQ(ray.getDirection(), direction_expected);
}

// Tests the standard constructor
TEST(GraphicsRay, StandardConstructor)
{
    const gfx::Vector4 origin_expected{ 3.0, 2.0, 1.0, 1.0 };
    const gfx::Vector4 direction_expected{ 1.0, -1.0, 0.0, 0.0 };
    const gfx::Ray ray{ origin_expected, direction_expected };

    ASSERT_EQ(ray.getOrigin(), origin_expected);
    ASSERT_EQ(ray.getDirection(), direction_expected);
}

// Tests the copy constructor
TEST(GraphicsRay, CopyConstructor)
{
    const gfx::Vector4 origin_expected{ 3.0, 2.0, 1.0, 1.0 };
    const gfx::Vector4 direction_expected{ 1.0, -1.0, 0.0, 0.0 };
    const gfx::Ray ray_src{ origin_expected, direction_expected };
    const gfx::Ray ray_cpy{ ray_src };

    ASSERT_EQ(ray_cpy.getOrigin(), origin_expected);
    ASSERT_EQ(ray_cpy.getDirection(), direction_expected);
}

// Tests the assignment operator
TEST(GraphicsRay, AssignmentOperator)
{
    const gfx::Vector4 origin_expected{ 3.0, 2.0, 1.0, 1.0 };
    const gfx::Vector4 direction_expected{ 1.0, -1.0, 0.0, 0.0 };
    gfx::Ray ray_a{ };
    const gfx::Ray ray_b{ origin_expected, direction_expected };

    ray_a = ray_b;

    ASSERT_EQ(ray_a.getOrigin(), origin_expected);
    ASSERT_EQ(ray_a.getDirection(), direction_expected);
}