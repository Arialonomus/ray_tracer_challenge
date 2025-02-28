#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "cube.hpp"

#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the default constructor
TEST(GraphicsCube, DefaultConstructor)
{
    const gfx::Cube cube{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    ASSERT_EQ(cube.getTransform(), transform_expected);
    ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the standard constructor
TEST(GraphicsCube, StandardConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected };
    const gfx::Cube cube{ gfx::createScalingMatrix(5), material_expected };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    ASSERT_EQ(cube.getTransform(), transform_expected);
    ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the standard constructor (with default material)
TEST(GraphicsCube, StandardConstructorDefaultMaterial)
{
    const gfx::Cube cube{ gfx::createScalingMatrix(5) };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };

    ASSERT_EQ(cube.getTransform(), transform_expected);
    ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the standard constructor (with default transform)
TEST(GraphicsCube, StandardConstructorDefaultTransform)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected };
    const gfx::Cube cube{ material_expected };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(cube.getTransform(), transform_expected);
    ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the copy constructor
TEST(GraphicsCube, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected };
    const gfx::Cube cube_src{ transform_expected, material_expected };
    const gfx::Cube cube_cpy{ cube_src };

    ASSERT_EQ(cube_cpy.getTransform(), transform_expected);
    ASSERT_EQ(cube_cpy.getMaterial(), material_expected);
}

// Tests the assignment operator
TEST(GraphicsCube, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected };
    const gfx::Cube cube_a{ transform_expected, material_expected };
    gfx::Cube cube_b{ };

    cube_b = cube_a;

    ASSERT_EQ(cube_b.getTransform(), transform_expected);
    ASSERT_EQ(cube_b.getMaterial(), material_expected);
}

// Tests the equality operator
TEST(GraphicsCube, EqualityOperator)
{
    const gfx::Cube cube_a{ gfx::createScalingMatrix(5) };
    const gfx::Cube cube_b{ gfx::createScalingMatrix(5) };

    ASSERT_TRUE(cube_a == cube_b);
}

// Tests the inequality operator
TEST(GraphicsCube, InequalityOperator)
{
    const gfx::Cube cube_a{ gfx::createScalingMatrix(5) };
    const gfx::Cube cube_b{ };

    ASSERT_TRUE(cube_a != cube_b);
}

// Tests getting the bounds of a cube
TEST(GraphicsCube, GetBounds)
{
    const gfx::Cube cube{ };
    const gfx::BoundingBox cube_bounds{ cube.getBounds() };

    const gfx::Vector4 cube_min_extent_expected{ gfx::createPoint(-1, -1, -1) };
    const gfx::Vector4 cube_min_extent_actual{ cube_bounds.getMinExtentPoint() };
    EXPECT_EQ(cube_min_extent_actual, cube_min_extent_expected);

    const gfx::Vector4 cube_max_extent_expected{ gfx::createPoint(1, 1, 1) };
    const gfx::Vector4 cube_max_extent_actual{ cube_bounds.getMaxExtentPoint() };
    EXPECT_EQ(cube_max_extent_actual, cube_max_extent_expected);
}

// Tests a ray intersecting a cube at each face, as well as inside
TEST(GraphicsCube, RayCubeIntersections)
{
    const gfx::Cube cube{ };    // Assume an axis-aligned bounding box

    // -Test Case Index Key-
    // [0] - +x face
    // [1] - -x face
    // [2] - +y face
    // [3] - -y face
    // [4] - +z face
    // [5] - -z face
    // [6] - inside the cube

    const std::vector<gfx::Vector4> origin_list{
        gfx::createPoint(5, 0.5 ,0),
        gfx::createPoint(-5, 0.5, 0),
        gfx::createPoint(0.5, 5, 0),
        gfx::createPoint(0.5, -5, 0),
        gfx::createPoint(0.5, 0, 5),
        gfx::createPoint(0.5, 0, -5),
        gfx::createPoint(0, 0.5, 0)
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(-1, 0, 0),
            gfx::createVector(1, 0, 0),
            gfx::createVector(0, -1, 0),
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, 0, -1),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, 1)
    };

    const std::vector<std::pair<double, double>> intersection_t_expected_list {
            { 4, 6 },
            { 4, 6 },
            { 4, 6 },
            { 4, 6 },
            { 4, 6 },
            { 4, 6 },
            { -1, 1 }
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());
    ASSERT_TRUE(origin_list.size() == intersection_t_expected_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            direction_list[i] };

        std::vector<gfx::Intersection> intersections{ cube.getObjectIntersections(ray) };

        const auto [ t1_expected, t2_expected ] { intersection_t_expected_list[i] };
        EXPECT_FLOAT_EQ(intersections[0].getT(), t1_expected);
        EXPECT_FLOAT_EQ(intersections[1].getT(), t2_expected);
    }
}

// Tests a ray intersecting a cube at each face, as well as originating from inside
TEST(GraphicsCube, RayCubeMisses)
{
    const gfx::Cube cube{ };    // Assume an axis-aligned bounding box

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(-2, 0, 0),
            gfx::createPoint(0, -2 ,0),
            gfx::createPoint(0, 0, -2),
            gfx::createPoint(2, 0, 2),
            gfx::createPoint(0, 2, 2),
            gfx::createPoint(2, 2, 0)
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0.2673, 0.5345, 0.8018),
            gfx::createVector(0.8018, 0.2673, 0.5345),
            gfx::createVector(0.5345, 0.8018, 0.2673),
            gfx::createVector(0, 0, -1),
            gfx::createVector(0, -1, 0),
            gfx::createVector(-1, 0, 0)
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            direction_list[i] };

        std::vector<gfx::Intersection> intersections{ cube.getObjectIntersections(ray) };

        EXPECT_TRUE(intersections.empty());
    }
}

// Tests finding the surface normal for a cube at various points
TEST(GraphicsCube, GetSurfaceNormal)
{
    const gfx::Cube cube{ };    // Assume an axis-aligned bounding box

    const std::vector<gfx::Vector4> point_list{
            gfx::createPoint(1, 0.5, -0.8),
            gfx::createPoint(-1, -0.2, 0.9),
            gfx::createPoint(-0.4, 1, -0.1),
            gfx::createPoint(0.3, -1, 0.7),
            gfx::createPoint(-0.6, 0.3, 1),
            gfx::createPoint(0.4, 0.4, -1),
            gfx::createPoint(1, 1, 1),
            gfx::createPoint(-1, -1, -1)
    };

    const std::vector<gfx::Vector4> surface_normaL_expected_list{
            gfx::createVector(1, 0, 0),
            gfx::createVector(-1, 0, 0),
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, -1, 0),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, -1),
            gfx::createVector(1, 0, 0),
            gfx::createVector(-1, 0, 0)
    };

    ASSERT_TRUE(point_list.size() == surface_normaL_expected_list.size());

    for (int i = 0; i < point_list.size(); ++i) {
        const gfx::Vector4 surface_normal_actual{ cube.getSurfaceNormalAt(point_list[i]) };
        EXPECT_EQ(surface_normal_actual, surface_normaL_expected_list[i]);
    }
}

#pragma clang diagnostic pop