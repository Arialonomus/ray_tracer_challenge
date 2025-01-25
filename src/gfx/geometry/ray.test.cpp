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

// Tests the vector list constructor
TEST(GraphicsRay, VectorListConstructor)
{
    const gfx::Vector4 origin_expected{ 3.0, 2.0, 1.0, 1.0 };
    const gfx::Vector4 direction_expected{ 1.0, -1.0, 0.0, 0.0 };
    const gfx::Ray ray{ origin_expected, direction_expected };

    ASSERT_EQ(ray.getOrigin(), origin_expected);
    ASSERT_EQ(ray.getDirection(), direction_expected);
}

// Tests the float list constructor
TEST(GraphicsRay, FloatListConstructor)
{
    const gfx::Vector4 origin_expected{ 3.0, 2.0, 1.0, 1.0 };
    const gfx::Vector4 direction_expected{ 1.0, -1.0, 0.0, 0.0 };
    const gfx::Ray ray{ 3, 2, 1,
                        1, -1, 0 };

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

// Tests the equality operator
TEST(GraphicsRay, EqualityOperator)
{
    const gfx::Ray ray_a{ gfx::createPoint(1, 2, 3),
                          gfx::createVector(0, 1, -1) };
    const gfx::Ray ray_b{ gfx::createPoint(1, 2, 3),
                          gfx::createVector(0, 1, -1) };

    ASSERT_TRUE(ray_a == ray_b);
}

// Tests the inequality operator
TEST(GraphicsRay, InequalityOperator)
{
    const gfx::Ray ray_a{ gfx::createPoint(1, 2, 3),
                          gfx::createVector(0, 1, -1) };
    const gfx::Ray ray_b{ };

    ASSERT_TRUE(ray_a != ray_b);
}

// Tests the position function
TEST(GraphicsRay, Position)
{
    const gfx::Ray ray{ gfx::createPoint(2, 3, 4),
                        gfx::createVector(1, 0, 0) };

    const gfx::Vector4 position_a_expected{ gfx::createPoint(2, 3, 4) };
    EXPECT_EQ(ray.position(0), position_a_expected);

    const gfx::Vector4 position_b_expected{ gfx::createPoint(3, 3, 4) };
    EXPECT_EQ(ray.position(1), position_b_expected);

    const gfx::Vector4 position_c_expected{ gfx::createPoint(1, 3, 4) };
    EXPECT_EQ(ray.position(-1), position_c_expected);

    const gfx::Vector4 position_d_expected{ gfx::createPoint(4.5, 3, 4) };
    EXPECT_EQ(ray.position(2.5), position_d_expected);
}

// Tests that Intersection structs correctly refer to the intersected object
TEST(GraphicsRay, IntersectionStruct)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ ray.getIntersections(sphere) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(&intersections.at(0).getObject(), &sphere);
    EXPECT_EQ(&intersections.at(1).getObject(), &sphere);
}

// Tests a ray intersecting a sphere at two points
TEST(GraphicsRay, RaySphereFullIntersection)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ ray.getIntersections(sphere) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 4.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 6.0);
}

// Tests a ray intersecting a sphere at one point (ray is tangent to the sphere)
TEST(GraphicsRay, RaySphereTangentIntersection)
{
    const gfx::Ray ray{ 0, 1, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ ray.getIntersections(sphere) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 5.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 5.0);
}

// Tests a ray missing a sphere
TEST(GraphicsRay, RaySphereMiss)
{
    const gfx::Ray ray{ 0, 2, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ ray.getIntersections(sphere) };

    EXPECT_EQ(intersections.size(), 0);
}

// Tests a ray originating inside a sphere
TEST(GraphicsRay, RayIntersectionOriginInSphere)
{
    const gfx::Ray ray{ 0, 0, 0,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ ray.getIntersections(sphere) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), -1.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 1.0);
}

// Tests a ray originating beyond a sphere
TEST(GraphicsRay, RayIntersectionOriginBeyondSphere)
{
    const gfx::Ray ray{ 0, 0, 5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ ray.getIntersections(sphere) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), -6.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), -4.0);
}