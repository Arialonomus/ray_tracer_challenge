#include "gtest/gtest.h"
#include "intersection.hpp"

#include "sphere.hpp"

// Tests the standard constructor
TEST(GraphicsIntersection, StandardConstructor)
{
    const gfx::Sphere sphere{ };
    const gfx::Intersection intersection{ 1.0, sphere };

    ASSERT_FLOAT_EQ(intersection.getT(), 1.0);
    ASSERT_EQ(&intersection.getObject(), &sphere);
}

// Tests the copy constructor
TEST(GraphicsIntersection, CopyConstructor)
{
    const gfx::Sphere sphere{ };
    const gfx::Intersection intersection_src{ 1.0, sphere };
    const gfx::Intersection intersection_cpy{ intersection_src };

    ASSERT_FLOAT_EQ(intersection_cpy.getT(), 1.0);
    ASSERT_EQ(&intersection_cpy.getObject(), &sphere);
}

// Tests the assignment operator
TEST(GraphicsIntersection, AssignmentOperator)
{
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Intersection intersection_a{ 1.0, sphere_a };
    gfx::Intersection intersection_b{ -2.0, sphere_b };

    intersection_b = intersection_a;

    ASSERT_FLOAT_EQ(intersection_b.getT(), 1.0);
    ASSERT_EQ(&intersection_b.getObject(), &sphere_a);
}

// Tests the equality operator
TEST(GraphicsIntersection, EqualityOperator)
{
    const gfx::Sphere sphere{ };
    const gfx::Intersection intersection_a{ 1.0, sphere };
    const gfx::Intersection intersection_b{ 1.0, sphere };

    ASSERT_TRUE(intersection_a == intersection_b);
}

// Tests the inequality operator
TEST(GraphicsIntersection, InequalityOperator)
{
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Intersection intersection_a{ 1.0, sphere_a };
    const gfx::Intersection intersection_b{ -2.0, sphere_b };

    ASSERT_TRUE(intersection_a != intersection_b);
}

// Tests the getHit functionality for 2-intersection groups when all intersections have positive t values
TEST(GraphicsIntersection, GetHitAllPositiveT)
{
    const gfx::Sphere sphere{ };

    const gfx::Intersection intersection_a{ 1, sphere };
    const gfx::Intersection intersection_b{ 2, sphere };
    std::vector<gfx::Intersection> intersections{ intersection_a, intersection_b };

    const std::optional<gfx::Intersection> hit_actual{ gfx::getHit(intersections) };

    EXPECT_TRUE(hit_actual.has_value());
    EXPECT_EQ(hit_actual.value(), intersection_a);
}

// Tests the getHit functionality for 2-intersection groups when one intersection has a negative t value
TEST(GraphicsIntersection, GetHitSomePositiveT)
{
    const gfx::Sphere sphere{ };

    const gfx::Intersection intersection_a{ -1, sphere };
    const gfx::Intersection intersection_b{ 1, sphere };
    std::vector<gfx::Intersection> intersections{ intersection_a, intersection_b };

    const std::optional<gfx::Intersection> hit_actual{ gfx::getHit(intersections) };

    EXPECT_TRUE(hit_actual.has_value());
    EXPECT_EQ(hit_actual.value(), intersection_b);
}

// Tests the getHit functionality for 2-intersection groups when all intersections have positive t values
TEST(GraphicsIntersection, GetHitAllNegativeT)
{
    const gfx::Sphere sphere{ };

    const gfx::Intersection intersection_a{ -2, sphere };
    const gfx::Intersection intersection_b{ -1, sphere };
    std::vector<gfx::Intersection> intersections{ intersection_a, intersection_b };

    const std::optional<gfx::Intersection> hit_actual{ gfx::getHit(intersections) };

    EXPECT_FALSE(hit_actual.has_value());
}

// Tests the getHit functionality for intersection groups with multiple positive t values
TEST(GraphicsIntersection, GetHitMultiplePositiveT)
{
    const gfx::Sphere sphere{ };

    const gfx::Intersection intersection_a{ 5, sphere };
    const gfx::Intersection intersection_b{ 7, sphere };
    const gfx::Intersection intersection_c{ -3, sphere };
    const gfx::Intersection intersection_d{ 2, sphere };
    std::vector<gfx::Intersection> intersections{ intersection_a, intersection_b, intersection_c, intersection_d };

    const std::optional<gfx::Intersection> hit_actual{ gfx::getHit(intersections) };

    EXPECT_TRUE(hit_actual.has_value());
    EXPECT_EQ(hit_actual.value(), intersection_d);
}