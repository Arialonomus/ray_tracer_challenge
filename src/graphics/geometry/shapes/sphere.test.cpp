#include "gtest/gtest.h"
#include "sphere.hpp"

#include <cmath>

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"

// Tests the default constructor
TEST(GraphicsSphere, DefaultConstructor)
{
    const gfx::Sphere sphere{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    ASSERT_EQ(sphere.getTransform(), transform_expected);
    ASSERT_EQ(sphere.getMaterial(), material_expected);
}

// Tests the standard constructor
TEST(GraphicsSphere, StandardConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Sphere sphere{ gfx::createScalingMatrix(5), material_expected };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    ASSERT_EQ(sphere.getTransform(), transform_expected);
    ASSERT_EQ(sphere.getMaterial(), material_expected);
}

// Tests the standard constructor (with default material)
TEST(GraphicsSphere, StandardConstructorDefaultMaterial)
{
    const gfx::Sphere sphere{ gfx::createScalingMatrix(5) };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };

    ASSERT_EQ(sphere.getTransform(), transform_expected);
    ASSERT_EQ(sphere.getMaterial(), material_expected);
}

// Tests the standard constructor (with default transform)
TEST(GraphicsSphere, StandardConstructorDefaultTransform)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Sphere sphere{ material_expected };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(sphere.getTransform(), transform_expected);
    ASSERT_EQ(sphere.getMaterial(), material_expected);
}

// Tests the copy constructor
TEST(GraphicsSphere, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Sphere sphere_src{ transform_expected, material_expected };
    const gfx::Sphere sphere_cpy{ sphere_src };

    ASSERT_EQ(sphere_cpy.getTransform(), transform_expected);
    ASSERT_EQ(sphere_cpy.getMaterial(), material_expected);
}

// Tests the assignment operator
TEST(GraphicsSphere, AssignmentOperator)
{

    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Sphere sphere_a{ transform_expected, material_expected };
    gfx::Sphere sphere_b{ };

    sphere_b = sphere_a;

    ASSERT_EQ(sphere_b.getTransform(), transform_expected);
    ASSERT_EQ(sphere_b.getMaterial(), material_expected);
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

// Tests getting the surface normal at various points
TEST(GraphicsSphere, GetSurfaceNormal)
{
    const gfx::Sphere sphere{ };

    // Test the normal on a sphere at a point on the x-axis
    const gfx::Vector4 normal_x_expected{ 1, 0, 0, 0 };
    const gfx::Vector4 normal_x_actual{ sphere.getSurfaceNormal(gfx::createPoint(1, 0, 0)) };

    EXPECT_EQ(normal_x_actual, normal_x_expected);

    // Test the normal on a sphere at a point on the y-axis
    const gfx::Vector4 normal_y_expected{ 0, 1, 0, 0 };
    const gfx::Vector4 normal_y_actual{ sphere.getSurfaceNormal(gfx::createPoint(0, 1, 0)) };

    EXPECT_EQ(normal_y_actual, normal_y_expected);

    // Test the normal on a sphere at a point on the z-axis
    const gfx::Vector4 normal_z_expected{ 0, 0, 1, 0 };
    const gfx::Vector4 normal_z_actual{ sphere.getSurfaceNormal(gfx::createPoint(0, 0, 1)) };

    EXPECT_EQ(normal_z_actual, normal_z_expected);

    // Test the normal on a sphere at a non_axial point
    const gfx::Vector4 normal_nonaxial_expected{ std::sqrtf(3) / 3,
                                                 std::sqrtf(3) / 3,
                                                 std::sqrtf(3) / 3,
                                                 0 };
    const gfx::Vector4 normal_nonaxial_actual{
        sphere.getSurfaceNormal(gfx::createPoint(
                std::sqrtf(3) / 3,
                std::sqrtf(3) / 3,
                std::sqrtf(3) / 3)) };

    EXPECT_EQ(normal_nonaxial_actual, normal_nonaxial_expected);

    // Test that the surface normal is a normalized vector
    EXPECT_EQ(normalize(normal_nonaxial_actual), normal_nonaxial_expected);
}

// Tests getting the surface normal at various points on a transformed sphere
TEST(GraphicsSphere, GetSurfaceNormaTransformed)
{
    // Test the normal at a point on a translated sphere
    const gfx::Sphere sphere_translated{ gfx::createTranslationMatrix(0, 1, 0)};
    const gfx::Vector4 normal_translate_expected{ 0, 0.707107, -0.707107, 0 };
    const gfx::Vector4 normal_translate_actual{
        sphere_translated.getSurfaceNormal(gfx::createPoint(0, 1.70711, -0.70711)) };

    EXPECT_EQ(normal_translate_actual, normal_translate_expected);

    // Test the normal at a point on a scaled and rotated sphere
    const gfx::Sphere sphere_transformed{
        gfx::createScalingMatrix(1, 0.5, 1) * gfx::createZRotationMatrix(M_PI / 5) };
    const gfx::Vector4 normal_transformed_expected{ 0, 0.970143, -0.242536, 0 };
    const gfx::Vector4 normal_transformed_actual{
        sphere_transformed.getSurfaceNormal(gfx::createPoint(0, M_PI_2, -M_PI_2)) };

    EXPECT_EQ(normal_transformed_actual, normal_transformed_expected);
}

// Tests that Intersections returned from getIntersections correctly refer to the intersected object
TEST(GraphicsSphere, GetIntersectionsCorrectReference)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ sphere.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(&intersections.at(0).getObject(), &sphere);
    EXPECT_EQ(&intersections.at(1).getObject(), &sphere);
}

// Tests a ray intersecting a sphere at two points
TEST(GraphicsSphere, RaySphereFullIntersection)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ sphere.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 4.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 6.0);
}

// Tests a ray intersecting a sphere at one point (ray is tangent to the sphere)
TEST(GraphicsSphere, RaySphereTangentIntersection)
{
    const gfx::Ray ray{ 0, 1, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ sphere.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 5.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 5.0);
}

// Tests a ray missing a sphere
TEST(GraphicsSphere, RaySphereMiss)
{
    const gfx::Ray ray{ 0, 2, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ sphere.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 0);
}

// Tests a ray originating inside a sphere
TEST(GraphicsSphere, RaySphereIntersectionOriginInSphere)
{
    const gfx::Ray ray{ 0, 0, 0,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ sphere.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), -1.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 1.0);
}

// Tests a ray originating beyond a sphere
TEST(GraphicsSphere, RaySphereIntersectionOriginBeyondSphere)
{
    const gfx::Ray ray{ 0, 0, 5,
                        0, 0, 1 };
    const gfx::Sphere sphere{ };    // Assume a unit sphere at the origin

    std::vector<gfx::Intersection> intersections{ sphere.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), -6.0);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), -4.0);
}

// Tests ray-sphere intersection with a scaled sphere
TEST(GraphicsSphere, RayScaledSphereIntersection)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere_scaled{ gfx::createScalingMatrix(2) };

    std::vector<gfx::Intersection> intersections{ sphere_scaled.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 3);
    EXPECT_FLOAT_EQ(intersections.at(1).getT(), 7);
}

// Tests ray-sphere intersection with a translated sphere
TEST(GraphicsSphere, RayTranslatedSphereIntersection)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };
    const gfx::Sphere sphere_translated{ gfx::createTranslationMatrix(5, 0, 0) };

    std::vector<gfx::Intersection> intersections{ sphere_translated.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 0);
}