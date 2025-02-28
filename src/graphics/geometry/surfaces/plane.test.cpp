#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "plane.hpp"

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the default constructor
TEST(GraphicsPlane, DefaultConstructor)
{
const gfx::Plane plane{ };
const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
const gfx::Material material_expected{ };

ASSERT_EQ(plane.getTransform(), transform_expected);
ASSERT_EQ(plane.getMaterial(), material_expected);
}

// Tests the standard constructor
TEST(GraphicsPlane, StandardConstructor)
{
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected };
const gfx::Plane plane{ gfx::createScalingMatrix(5), material_expected };
const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

ASSERT_EQ(plane.getTransform(), transform_expected);
ASSERT_EQ(plane.getMaterial(), material_expected);
}

// Tests the standard constructor (with default material)
TEST(GraphicsPlane, StandardConstructorDefaultMaterial)
{
const gfx::Plane plane{ gfx::createScalingMatrix(5) };
const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
const gfx::Material material_expected{ };

ASSERT_EQ(plane.getTransform(), transform_expected);
ASSERT_EQ(plane.getMaterial(), material_expected);
}

// Tests the standard constructor (with default transform)
TEST(GraphicsPlane, StandardConstructorDefaultTransform)
{
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected };
const gfx::Plane plane{ material_expected };
const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

ASSERT_EQ(plane.getTransform(), transform_expected);
ASSERT_EQ(plane.getMaterial(), material_expected);
}

// Tests the copy constructor
TEST(GraphicsPlane, CopyConstructor)
{
const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected };
const gfx::Plane plane_src{ transform_expected, material_expected };
const gfx::Plane plane_cpy{ plane_src };

ASSERT_EQ(plane_cpy.getTransform(), transform_expected);
ASSERT_EQ(plane_cpy.getMaterial(), material_expected);
}

// Tests the assignment operator
TEST(GraphicsPlane, AssignmentOperator)
{

const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected };
const gfx::Plane plane_a{ transform_expected, material_expected };
gfx::Plane plane_b{ };

plane_b = plane_a;

ASSERT_EQ(plane_b.getTransform(), transform_expected);
ASSERT_EQ(plane_b.getMaterial(), material_expected);
}

// Tests the equality operator
TEST(GraphicsPlane, EqualityOperator)
{
const gfx::Plane plane_a{ gfx::createScalingMatrix(5) };
const gfx::Plane plane_b{ gfx::createScalingMatrix(5) };

ASSERT_TRUE(plane_a == plane_b);
}

// Tests the inequality operator
TEST(GraphicsPlane, InequalityOperator)
{
const gfx::Plane plane_a{ gfx::createScalingMatrix(5) };
const gfx::Plane plane_b{ };

ASSERT_TRUE(plane_a != plane_b);
}

// Tests getting the bounds of a plane
TEST(GraphicsPlane, GetBounds)
{
    const gfx::Plane plane{ };
    const gfx::BoundingBox plane_bounds{ plane.getBounds() };

    const gfx::Vector4 plane_min_extent_expected{ gfx::createPoint(-std::numeric_limits<double>::infinity(),
                                                                   0,
                                                                   -std::numeric_limits<double>::infinity()) };
    const gfx::Vector4 plane_min_extent_actual{ plane_bounds.getMinExtentPoint() };
    EXPECT_EQ(plane_min_extent_actual, plane_min_extent_expected);

    const gfx::Vector4 plane_max_extent_expected{ gfx::createPoint(std::numeric_limits<double>::infinity(),
                                                                   0,
                                                                   std::numeric_limits<double>::infinity()) };
    const gfx::Vector4 plane_max_extent_actual{ plane_bounds.getMaxExtentPoint() };
    EXPECT_EQ(plane_max_extent_actual, plane_max_extent_expected);
}

// Tests that the normal of a plane is constant everywhere
TEST(GraphicsPlane, NormalVectorIsConstant)
{
    const gfx::Plane plane{ };
    const gfx::Vector4 normal_expected{ gfx::createVector(0, 1, 0)};

    const gfx::Vector4 normal_a_actual{ plane.getSurfaceNormalAt(gfx::createPoint(0, 0, 0)) };
    EXPECT_EQ(normal_a_actual, normal_expected);

    const gfx::Vector4 normal_b_actual{ plane.getSurfaceNormalAt(gfx::createPoint(10, 0, -10)) };
    EXPECT_EQ(normal_b_actual, normal_expected);

    const gfx::Vector4 normal_c_actual{ plane.getSurfaceNormalAt(gfx::createPoint(-5, 0, 150)) };
    EXPECT_EQ(normal_c_actual, normal_expected);
}

// Tests calculating intersections with a ray parallel to the plane
TEST(GraphicsPlane, RayPlaneIntersectionParallelRay)
{
    const gfx::Plane plane{ };
    const gfx::Ray parallel_ray{ 0, 10, 0,
                                 0, 0, 1} ;

    auto intersections{ plane.getObjectIntersections(parallel_ray) };
    EXPECT_EQ(intersections.size(), 0);
}

// Tests calculating intersections with a ray coplanar to the plane
TEST(GraphicsPlane, RayPlaneIntersectionCoplanarRay)
{
    const gfx::Plane plane{ };
    const gfx::Ray coplanar_ray{ 0, 0, 0,
                                 0, 0, 1} ;

    auto intersections{ plane.getObjectIntersections(coplanar_ray) };
    EXPECT_EQ(intersections.size(), 0);
}

// Tests calculating intersections with a ray intersecting the plane from above
TEST(GraphicsPlane, RayPlaneIntersectionRayOriginAbove)
{
    const gfx::Plane plane{ };
    const gfx::Ray ray_origin_above{ 0, 1, 0,
                                 0, -1, 0} ;

    auto intersections{ plane.getObjectIntersections(ray_origin_above) };
    ASSERT_EQ(intersections.size(), 1);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 1);
    EXPECT_EQ(&intersections.at(0).getObject(), &plane);
}

// Tests calculating intersections with a ray intersecting the plane from below
TEST(GraphicsPlane, RayPlaneIntersectionRayOriginBelow)
{
    const gfx::Plane plane{ };
    const gfx::Ray ray_origin_below{ 0, -1, 0,
                                     0, 1, 0} ;

    auto intersections{ plane.getObjectIntersections(ray_origin_below) };
    ASSERT_EQ(intersections.size(), 1);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 1);
    EXPECT_EQ(&intersections.at(0).getObject(), &plane);
}

#pragma clang diagnostic pop