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

// Tests the standard constructor for detailed intersections (when the intersection is outside the object)
TEST(GraphicsIntersection, DetailedStandardConstructorOutside)
{
    const gfx::Sphere sphere{ };
    const gfx::Intersection base_intersection{ 4, sphere };
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::DetailedIntersection detailed_intersection{ base_intersection, ray };

    ASSERT_FLOAT_EQ(detailed_intersection.getT(), 4);
    ASSERT_EQ(&detailed_intersection.getObject(), &sphere);
    ASSERT_EQ(detailed_intersection.getSurfacePosition(), gfx::createPoint(0, 0, -1));
    ASSERT_EQ(detailed_intersection.getSurfaceNormal(), gfx::createVector(0, 0, -1));
    ASSERT_EQ(detailed_intersection.getViewVector(), gfx::createVector(0, 0, -1));
    ASSERT_FALSE(detailed_intersection.isInsideObject());
}

// Tests the standard constructor for detailed intersections (when the intersection is inside the object)
TEST(GraphicsIntersection, DetailedStandardConstructorInside)
{
    const gfx::Sphere sphere{ };
    const gfx::Intersection base_intersection{ 1, sphere };
    const gfx::Ray ray{ 0, 0, 0,
                        0, 0, 1 };
    const gfx::DetailedIntersection detailed_intersection{ base_intersection, ray };

    ASSERT_FLOAT_EQ(detailed_intersection.getT(), 1);
    ASSERT_EQ(&detailed_intersection.getObject(), &sphere);
    ASSERT_EQ(detailed_intersection.getSurfacePosition(), gfx::createPoint(0, 0, 1));
    ASSERT_EQ(detailed_intersection.getSurfaceNormal(), gfx::createVector(0, 0, -1));
    ASSERT_EQ(detailed_intersection.getViewVector(), gfx::createVector(0, 0, -1));
    ASSERT_TRUE(detailed_intersection.isInsideObject());
}

// Tests the copy constructor for detailed intersections
TEST(GraphicsIntersection, DetailedCopyConstructor)
{
    const gfx::Sphere sphere{ };
    const gfx::Intersection base_intersection{ 4, sphere };
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::DetailedIntersection detailed_intersection_src{ base_intersection, ray };
    const gfx::DetailedIntersection detailed_intersection_cpy{ detailed_intersection_src };

    ASSERT_FLOAT_EQ(detailed_intersection_cpy.getT(), 4);
    ASSERT_EQ(&detailed_intersection_cpy.getObject(), &sphere);
    ASSERT_EQ(detailed_intersection_cpy.getSurfacePosition(), gfx::createPoint(0, 0, -1));
    ASSERT_EQ(detailed_intersection_cpy.getSurfaceNormal(), gfx::createVector(0, 0, -1));
    ASSERT_EQ(detailed_intersection_cpy.getViewVector(), gfx::createVector(0, 0, -1));
    ASSERT_FALSE(detailed_intersection_cpy.isInsideObject());
}

// Tests the assignment operator for detailed intersections
TEST(GraphicsIntersection, DetailedAssignmentOperator)
{
    const gfx::Sphere sphere_a{ };
    const gfx::Intersection base_intersection_a{ 4, sphere_a };
    const gfx::Ray ray_a{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::DetailedIntersection detailed_intersection_a{ base_intersection_a, ray_a };
    const gfx::Sphere sphere_b{ };
    const gfx::Intersection base_intersection_b{ 1, sphere_b };
    const gfx::Ray ray_b{ 0, 0, -10,
                          1, 1, 1 };
    gfx::DetailedIntersection detailed_intersection_b{ base_intersection_b, ray_b };

    detailed_intersection_b = detailed_intersection_a;

    ASSERT_FLOAT_EQ(detailed_intersection_b.getT(), 4);
    ASSERT_EQ(&detailed_intersection_b.getObject(), &sphere_a);
    ASSERT_EQ(detailed_intersection_b.getSurfacePosition(), gfx::createPoint(0, 0, -1));
    ASSERT_EQ(detailed_intersection_b.getSurfaceNormal(), gfx::createVector(0, 0, -1));
    ASSERT_EQ(detailed_intersection_b.getViewVector(), gfx::createVector(0, 0, -1));
    ASSERT_FALSE(detailed_intersection_b.isInsideObject());
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