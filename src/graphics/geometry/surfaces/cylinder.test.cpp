#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "cylinder.hpp"

#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the default constructors
TEST(GraphicsCylinder, DefaultConstructor)
{
    const gfx::Cylinder cylinder_unbounded{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    // Test an unbounded cylinder
    const gfx::Material material_expected{ };

    ASSERT_EQ(cylinder_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMin()));
    ASSERT_TRUE(cylinder_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMax()));
    ASSERT_TRUE(cylinder_unbounded.getYMax() > 0);
    ASSERT_FALSE(cylinder_unbounded.isClosed());

    // Test a bounded cylinder
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cylinder cylinder_bounded{ y_min_expected, y_max_expected };

    ASSERT_EQ(cylinder_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMax(), y_max_expected);
    ASSERT_FALSE(cylinder_bounded.isClosed());
}

// Tests the material-only constructors
TEST(GraphicsCylinder, StandardConstructorDefaultMaterial)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };

    // Test an unbounded cylinder
    const gfx::Cylinder cylinder_unbounded{ transform_expected };

    ASSERT_EQ(cylinder_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMin()));
    ASSERT_TRUE(cylinder_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMax()));
    ASSERT_TRUE(cylinder_unbounded.getYMax() > 0);
    ASSERT_FALSE(cylinder_unbounded.isClosed());

    // Test a bounded cylinder
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cylinder cylinder_bounded{ transform_expected, y_min_expected, y_max_expected };

    ASSERT_EQ(cylinder_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMax(), y_max_expected);
    ASSERT_FALSE(cylinder_bounded.isClosed());
}

// Tests the transform-only constructors
TEST(GraphicsCylinder, StandardConstructorDefaultTransform)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    // Test an unbounded cylinder
    const gfx::Cylinder cylinder_unbounded{ material_expected };

    ASSERT_EQ(cylinder_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMin()));
    ASSERT_TRUE(cylinder_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMax()));
    ASSERT_TRUE(cylinder_unbounded.getYMax() > 0);
    ASSERT_FALSE(cylinder_unbounded.isClosed());

    // Test a bounded cylinder
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cylinder cylinder_bounded{ material_expected, y_min_expected, y_max_expected };

    ASSERT_EQ(cylinder_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMax(), y_max_expected);
    ASSERT_FALSE(cylinder_bounded.isClosed());
}

// Tests the standard constructors
TEST(GraphicsCylinder, StandardConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    // Test an unbounded cylinder
    const gfx::Cylinder cylinder_unbounded{ transform_expected, material_expected };

    ASSERT_EQ(cylinder_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMin()));
    ASSERT_TRUE(cylinder_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cylinder_unbounded.getYMax()));
    ASSERT_TRUE(cylinder_unbounded.getYMax() > 0);
    ASSERT_FALSE(cylinder_unbounded.isClosed());

    // Test a bounded cylinder (with end caps)
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cylinder cylinder_bounded{ transform_expected,
                                          material_expected,
                                          y_min_expected,
                                          y_max_expected,
                                          true };

    ASSERT_EQ(cylinder_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder_bounded.getYMax(), y_max_expected);
    ASSERT_TRUE(cylinder_bounded.isClosed());
}

// Tests the copy constructor
TEST(GraphicsCylinder, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };

    const gfx::Cylinder cylinder_src{ transform_expected,
                                      material_expected,
                                      y_min_expected,
                                      y_max_expected };
    const gfx::Cylinder cylinder_cpy{ cylinder_src };

    ASSERT_EQ(cylinder_cpy.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_cpy.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cylinder_cpy.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder_cpy.getYMax(), y_max_expected);
    ASSERT_FALSE(cylinder_cpy.isClosed());
}

// Tests the assignment operator
TEST(GraphicsCylinder, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };

    const gfx::Cylinder cylinder_a{ transform_expected,
                                    material_expected,
                                    y_min_expected,
                                    y_max_expected };
    gfx::Cylinder cylinder_b{ };

    cylinder_b = cylinder_a;

    ASSERT_EQ(cylinder_b.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_b.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cylinder_b.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder_b.getYMax(), y_max_expected);
    ASSERT_FALSE(cylinder_b.isClosed());
}

// Tests the mutators
TEST(GraphicsCylinder, Mutators)
{
    gfx::Cylinder cylinder{ };

    // Test setting y_min and y_max with values
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };

    cylinder.setYMin(y_min_expected);
    ASSERT_FLOAT_EQ(cylinder.getYMin(), y_min_expected);

    cylinder.setYMax(y_max_expected);
    ASSERT_FLOAT_EQ(cylinder.getYMax(), y_max_expected);

    // Test unbounding y_min and y_max individually
    cylinder.unboundYMin();
    ASSERT_TRUE(std::isinf(cylinder.getYMin()));
    ASSERT_TRUE(cylinder.getYMin() < 0);

    cylinder.unboundYMax();
    ASSERT_TRUE(std::isinf(cylinder.getYMax()));
    ASSERT_TRUE(cylinder.getYMax() > 0);

    // Test bounding y_min and y_max at the same time
    cylinder.setCylinderBounds(y_min_expected, y_max_expected);
    ASSERT_FLOAT_EQ(cylinder.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cylinder.getYMax(), y_max_expected);

    // Test unbounding y_min and y_max at the same time
    cylinder.unboundCylinder();
    ASSERT_TRUE(std::isinf(cylinder.getYMin()));
    ASSERT_TRUE(cylinder.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cylinder.getYMax()));
    ASSERT_TRUE(cylinder.getYMax() > 0);

    // Test capping the cylinder
    cylinder.capCylinder();
    ASSERT_TRUE(cylinder.isClosed());

    // Test uncapping the cylinder
    cylinder.uncapCylinder();
    ASSERT_FALSE(cylinder.isClosed());
}

// Tests the equality operator
TEST(GraphicsCylinder, EqualityOperator)
{
    const gfx::Cylinder cylinder_a{
        gfx::createScalingMatrix(5),
        gfx::createGlassyMaterial(),
        1,
        2,
        true
    };
    const gfx::Cylinder cylinder_b{
        gfx::createScalingMatrix(5),
        gfx::createGlassyMaterial(),
        1,
        2,
        true
    };

    ASSERT_TRUE(cylinder_a == cylinder_b);
}

// Tests the inequality operator
TEST(GraphicsCylinder, InequalityOperator)
{
    const gfx::Cylinder cylinder_a{
            gfx::createScalingMatrix(5),
            gfx::createGlassyMaterial(),
            1,
            2,
            true
    };
    const gfx::Cylinder cylinder_b{ };

    ASSERT_TRUE(cylinder_a != cylinder_b);
}

// Tests getting the bounds of a cylinder
TEST(GraphicsCylinder, GetBounds)
{
    // Test getting the bounding box of an unbounded cylinder
    const gfx::Cylinder cylinder_unbounded{ };
    const gfx::BoundingBox cylinder_unbounded_bounds{ cylinder_unbounded.getBounds() };

    const gfx::Vector4 cylinder_unbounded_min_extent_expected{ gfx::createPoint(-1,
                                                                                -std::numeric_limits<double>::infinity(),
                                                                                -1) };
    const gfx::Vector4 cylinder_unbounded_min_extent_actual{ cylinder_unbounded_bounds.getMinExtentPoint() };
    EXPECT_EQ(cylinder_unbounded_min_extent_actual, cylinder_unbounded_min_extent_expected);

    const gfx::Vector4 cylinder_unbounded_max_extent_expected{ gfx::createPoint(1,
                                                                                std::numeric_limits<double>::infinity(),
                                                                                1) };
    const gfx::Vector4 cylinder_unbounded_max_extent_actual{ cylinder_unbounded_bounds.getMaxExtentPoint() };
    EXPECT_EQ(cylinder_unbounded_max_extent_actual, cylinder_unbounded_max_extent_expected);

    // Test getting the bounding box of a bounded cylinder
    const gfx::Cylinder cylinder_bounded{ -5, 3 };
    const gfx::BoundingBox cylinder_bounded_bounds{ cylinder_bounded.getBounds() };

    const gfx::Vector4 cylinder_bounded_min_extent_expected{ gfx::createPoint(-1, -5, -1) };
    const gfx::Vector4 cylinder_bounded_min_extent_actual{ cylinder_bounded_bounds.getMinExtentPoint() };
    EXPECT_EQ(cylinder_bounded_min_extent_actual, cylinder_bounded_min_extent_expected);

    const gfx::Vector4 cylinder_bounded_max_extent_expected{ gfx::createPoint(1, 3, 1) };
    const gfx::Vector4 cylinder_bounded_max_extent_actual{ cylinder_bounded_bounds.getMaxExtentPoint() };
    EXPECT_EQ(cylinder_bounded_max_extent_actual, cylinder_bounded_max_extent_expected);
}

// Tests a ray missing an unbounded cylinder
TEST(GraphicsCylinder, RayCylinderMissesUnbounded)
{
    const gfx::Cylinder cylinder{ };    // Assume an unbounded unit cylinder centered at the origin

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(1, 0, 0),
            gfx::createPoint(0, 0 ,0),
            gfx::createPoint(0, 0, -5),
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, 1, 0),
            gfx::createVector(1, 1, 1),
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            gfx::normalize(direction_list[i]) };

        std::vector<gfx::Intersection> intersections{ cylinder.getObjectIntersections(ray) };

        EXPECT_TRUE(intersections.empty());
    }
}

// Tests ray intersections with an unbounded cylinder
TEST(GraphicsCylinder, RayCylinderHitsUnbounded)
{
    const gfx::Cylinder cylinder{ };    // Assume an unbounded unit cylinder centered at the origin

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(1, 0, -5),
            gfx::createPoint(0, 0, -5),
            gfx::createPoint(0.5, 0, -5),
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0.1, 1, 1),
    };

    const std::vector<std::pair<double, double>> intersection_t_expected_list {
            { 5, 5 },
            { 4, 6 },
            { 6.80798, 7.088724 }
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());
    ASSERT_TRUE(origin_list.size() == intersection_t_expected_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            gfx::normalize(direction_list[i]) };

        std::vector<gfx::Intersection> intersections{ cylinder.getObjectIntersections(ray) };

        const auto [ t1_expected, t2_expected ] { intersection_t_expected_list[i] };
        EXPECT_FLOAT_EQ(intersections[0].getT(), t1_expected);
        EXPECT_FLOAT_EQ(intersections[1].getT(), t2_expected);
    }
}

// Tests ray intersections with a bounded, uncapped cylinder
TEST(GraphicsCylinder, RayCylinderIntersectionsBoundedUncapped)
{
    const gfx::Cylinder cylinder{ 1, 2 };

    /* Test Case Index Key */
    // [0] - Ray cast diagonally upward from cylinder center
    // [1] - Ray cast perpendicular to the y-axis, above cylinder upper bound
    // [2] - Ray cast perpendicular to the y-axis, below cylinder lower bound
    // [3] - Ray cast perpendicular to the y-axis, co-planar with cylinder upper bound
    // [4] - Ray cast perpendicular to the y-axis, co-planar with cylinder lower bound
    // [5] - Ray cast perpendicular to the y-axis, through cylinder center

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(0, 1.5, 0),
            gfx::createPoint(0, 3, -5),
            gfx::createPoint(0, 0, -5),
            gfx::createPoint(0, 2, -5),
            gfx::createPoint(0, 1, -5),
            gfx::createPoint(0, 1.5, -2)
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0.1, 1, 0),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, 1),
            gfx::createVector(0, 0, 1)
    };

    const std::vector<size_t> intersection_count_expected_list {
            0,
            0,
            0,
            0,
            0,
            2
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());
    ASSERT_TRUE(origin_list.size() == intersection_count_expected_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            gfx::normalize(direction_list[i]) };

        std::vector<gfx::Intersection> intersections{ cylinder.getObjectIntersections(ray) };

        EXPECT_EQ(intersections.size(), intersection_count_expected_list[i]);
    }
}

// Tests ray intersections with a bounded, capped cylinder
TEST(GraphicsCylinder, RayCylinderIntersectionsBoundedCapped)
{
    const gfx::Cylinder cylinder{ 1, 2, true };

    /* Test Case Index Key */
    // [0] - Downward ray collinear with the y-axis, intersecting the center through the cylinder's upper end cap
    // [1] - Ray cast diagonally downward through the cylinder's upper end cap and out the side of the cylinder
    // [2] - Ray cast diagonally downward through the cylinder's upper end cap and exiting at the
    //       intersection of the side and lower end cap (corner case)
    // [3] - Ray cast diagonally upward through the cylinder's lower end cap and out the side of the cylinder
    // [4] - Ray cast diagonally upward through the cylinder's lower end cap and exiting at the
    //       intersection of the side and upper end cap (corner case)

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(0, 3, 0),
            gfx::createPoint(0, 3, -3),
            gfx::createPoint(0, 4, -2),
            gfx::createPoint(0, 0, -2),
            gfx::createPoint(0, -1, -2)
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0, -1, 0),
            gfx::createVector(0, -1, 2),
            gfx::createVector(0, -1, 1),
            gfx::createVector(0, 1, 2),
            gfx::createVector(0, 1, 1)
    };

    const std::vector<size_t> intersection_count_expected_list {
            2,
            2,
            2,
            2,
            2
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());
    ASSERT_TRUE(origin_list.size() == intersection_count_expected_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            gfx::normalize(direction_list[i]) };

        std::vector<gfx::Intersection> intersections{ cylinder.getObjectIntersections(ray) };

        EXPECT_EQ(intersections.size(), intersection_count_expected_list[i]);
    }
}

// Tests finding the surface normal on an unbounded cylinder
TEST(GraphicsCylinder, GetSurfaceNormalUnbounded)
{
    const gfx::Cylinder cylinder{ };    // Assume an unbounded unit cylinder centered at the origin

    const std::vector<gfx::Vector4> point_list{
            gfx::createPoint(1, 0, 0),
            gfx::createPoint(0, 5, -1),
            gfx::createPoint(0, -2, 1),
            gfx::createPoint(-1, 1, 0)
    };

    const std::vector<gfx::Vector4> surface_normaL_expected_list{
            gfx::createVector(1, 0, 0),
            gfx::createVector(0, 0, -1),
            gfx::createVector(0, 0, 1),
            gfx::createVector(-1, 0, 0)
    };

    ASSERT_TRUE(point_list.size() == surface_normaL_expected_list.size());

    for (int i = 0; i < point_list.size(); ++i) {
        const gfx::Vector4 surface_normal_actual{ cylinder.getSurfaceNormalAt(point_list[i]) };
        EXPECT_EQ(surface_normal_actual, surface_normaL_expected_list[i]);
    }
}

// Tests finding the surface normal on a cylinder's end caps
TEST(GraphicsCylinder, GetSurfaceNormalEndCaps)
{
    const gfx::Cylinder cylinder{ 1, 2, true };

    const std::vector<gfx::Vector4> point_list{
            gfx::createPoint(0, 1, 0),
            gfx::createPoint(0.5, 1, 0),
            gfx::createPoint(0, 1, 0.5),
            gfx::createPoint(0, 2, 0),
            gfx::createPoint(0.5, 2, 0),
            gfx::createPoint(0, 2, 0.5)
    };

    const std::vector<gfx::Vector4> surface_normaL_expected_list{
            gfx::createVector(0, -1, 0),
            gfx::createVector(0, -1, 0),
            gfx::createVector(0, -1, 0),
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, 1, 0)
    };

    ASSERT_TRUE(point_list.size() == surface_normaL_expected_list.size());

    for (int i = 0; i < point_list.size(); ++i) {
        const gfx::Vector4 surface_normal_actual{ cylinder.getSurfaceNormalAt(point_list[i]) };
        EXPECT_EQ(surface_normal_actual, surface_normaL_expected_list[i]);
    }
}

#pragma clang diagnostic pop