#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "cone.hpp"

#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the default constructors
TEST(GraphicsCone, DefaultConstructor)
{
    const gfx::Cone cone_unbounded{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    // Test an unbounded cone
    const gfx::Material material_expected{ };

    ASSERT_EQ(cone_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMin()));
    ASSERT_TRUE(cone_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMax()));
    ASSERT_TRUE(cone_unbounded.getYMax() > 0);
    ASSERT_FALSE(cone_unbounded.isClosed());

    // Test a bounded cone
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cone cone_bounded{ y_min_expected, y_max_expected };

    ASSERT_EQ(cone_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMax(), y_max_expected);
    ASSERT_FALSE(cone_bounded.isClosed());
}

// Tests the material-only constructors
TEST(GraphicsCone, StandardConstructorDefaultMaterial)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };

    // Test an unbounded cone
    const gfx::Cone cone_unbounded{ transform_expected };

    ASSERT_EQ(cone_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMin()));
    ASSERT_TRUE(cone_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMax()));
    ASSERT_TRUE(cone_unbounded.getYMax() > 0);
    ASSERT_FALSE(cone_unbounded.isClosed());

    // Test a bounded cone
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cone cone_bounded{ transform_expected, y_min_expected, y_max_expected };

    ASSERT_EQ(cone_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMax(), y_max_expected);
    ASSERT_FALSE(cone_bounded.isClosed());
}

// Tests the transform-only constructors
TEST(GraphicsCone, StandardConstructorDefaultTransform)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    // Test an unbounded cone
    const gfx::Cone cone_unbounded{ material_expected };

    ASSERT_EQ(cone_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMin()));
    ASSERT_TRUE(cone_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMax()));
    ASSERT_TRUE(cone_unbounded.getYMax() > 0);
    ASSERT_FALSE(cone_unbounded.isClosed());

    // Test a bounded cone
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cone cone_bounded{ material_expected, y_min_expected, y_max_expected };

    ASSERT_EQ(cone_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMax(), y_max_expected);
    ASSERT_FALSE(cone_bounded.isClosed());
}

// Tests the standard constructors
TEST(GraphicsCone, StandardConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    // Test an unbounded cone
    const gfx::Cone cone_unbounded{ transform_expected, material_expected };

    ASSERT_EQ(cone_unbounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_unbounded.getMaterial(), material_expected);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMin()));
    ASSERT_TRUE(cone_unbounded.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cone_unbounded.getYMax()));
    ASSERT_TRUE(cone_unbounded.getYMax() > 0);
    ASSERT_FALSE(cone_unbounded.isClosed());

    // Test a bounded cone (with end caps)
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };
    const gfx::Cone cone_bounded{ transform_expected,
                                          material_expected,
                                          y_min_expected,
                                          y_max_expected,
                                          true };

    ASSERT_EQ(cone_bounded.getTransform(), transform_expected);
    ASSERT_EQ(cone_bounded.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone_bounded.getYMax(), y_max_expected);
    ASSERT_TRUE(cone_bounded.isClosed());
}

// Tests the copy constructor
TEST(GraphicsCone, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };

    const gfx::Cone cone_src{ transform_expected,
                                      material_expected,
                                      y_min_expected,
                                      y_max_expected };
    const gfx::Cone cone_cpy{ cone_src };

    ASSERT_EQ(cone_cpy.getTransform(), transform_expected);
    ASSERT_EQ(cone_cpy.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cone_cpy.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone_cpy.getYMax(), y_max_expected);
    ASSERT_FALSE(cone_cpy.isClosed());
}

// Tests the assignment operator
TEST(GraphicsCone, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };

    const gfx::Cone cone_a{ transform_expected,
                                    material_expected,
                                    y_min_expected,
                                    y_max_expected };
    gfx::Cone cone_b{ };

    cone_b = cone_a;

    ASSERT_EQ(cone_b.getTransform(), transform_expected);
    ASSERT_EQ(cone_b.getMaterial(), material_expected);
    ASSERT_FLOAT_EQ(cone_b.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone_b.getYMax(), y_max_expected);
    ASSERT_FALSE(cone_b.isClosed());
}

// Tests the mutators
TEST(GraphicsCone, Mutators)
{
    gfx::Cone cone{ };

    // Test setting y_min and y_max with values
    const double y_min_expected{ -1 };
    const double y_max_expected{ 1 };

    cone.setYMin(y_min_expected);
    ASSERT_FLOAT_EQ(cone.getYMin(), y_min_expected);

    cone.setYMax(y_max_expected);
    ASSERT_FLOAT_EQ(cone.getYMax(), y_max_expected);

    // Test unbounding y_min and y_max individually
    cone.unboundYMin();
    ASSERT_TRUE(std::isinf(cone.getYMin()));
    ASSERT_TRUE(cone.getYMin() < 0);

    cone.unboundYMax();
    ASSERT_TRUE(std::isinf(cone.getYMax()));
    ASSERT_TRUE(cone.getYMax() > 0);

    // Test bounding y_min and y_max at the same time
    cone.setConeBounds(y_min_expected, y_max_expected);
    ASSERT_FLOAT_EQ(cone.getYMin(), y_min_expected);
    ASSERT_FLOAT_EQ(cone.getYMax(), y_max_expected);

    // Test unbounding y_min and y_max at the same time
    cone.unboundCone();
    ASSERT_TRUE(std::isinf(cone.getYMin()));
    ASSERT_TRUE(cone.getYMin() < 0);
    ASSERT_TRUE(std::isinf(cone.getYMax()));
    ASSERT_TRUE(cone.getYMax() > 0);

    // Test capping the cone
    cone.capCone();
    ASSERT_TRUE(cone.isClosed());

    // Test uncapping the cone
    cone.uncapCone();
    ASSERT_FALSE(cone.isClosed());
}

// Tests the equality operator
TEST(GraphicsCone, EqualityOperator)
{
    const gfx::Cone cone_a{
            gfx::createScalingMatrix(5),
            gfx::createGlassyMaterial(),
            1,
            2,
            true
    };
    const gfx::Cone cone_b{
            gfx::createScalingMatrix(5),
            gfx::createGlassyMaterial(),
            1,
            2,
            true
    };

    ASSERT_TRUE(cone_a == cone_b);
}

// Tests the inequality operator
TEST(GraphicsCone, InequalityOperator)
{
    const gfx::Cone cone_a{
            gfx::createScalingMatrix(5),
            gfx::createGlassyMaterial(),
            1,
            2,
            true
    };
    const gfx::Cone cone_b{ };

    ASSERT_TRUE(cone_a != cone_b);
}

// Tests ray intersections with an unbounded cone
TEST(GraphicsCone, RayConeHitsUnbounded)
{
    const gfx::Cone cone{ };    // Assume an unbounded double-napped cone centered at the origin

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(0, 0, -5),
            gfx::createPoint(0, 0, -5),
            gfx::createPoint(1, 1, -5),
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0, 0, 1),
            gfx::createVector(1, 1, 1),
            gfx::createVector(-0.5, -1, 1),
    };

    const std::vector<std::pair<double, double>> intersection_t_expected_list {
            { 5, 5 },
            { 8.660255, 8.660255 },
            { 4.550056, 49.44994 }
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());
    ASSERT_TRUE(origin_list.size() == intersection_t_expected_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            gfx::normalize(direction_list[i]) };

        std::vector<gfx::Intersection> intersections{ cone.getObjectIntersections(ray) };

        const auto [ t1_expected, t2_expected ] { intersection_t_expected_list[i] };
        EXPECT_FLOAT_EQ(intersections[0].getT(), t1_expected);
        EXPECT_FLOAT_EQ(intersections[1].getT(), t2_expected);
    }
}

// Tests intersecting an unbounded cone with a ray parallel to one of its halves
TEST(GraphicsCone, RayConeHitParallelToHalf)
{
    const gfx::Cone cone{ };
    const gfx::Ray ray{ gfx::createPoint(0, 0, -1),
                        gfx::normalize(gfx::createVector(0, 1, 1)) };

    std::vector<gfx::Intersection> intersections{ cone.getObjectIntersections(ray) };
    ASSERT_EQ(intersections.size(), 1);

    const double hit_t_expected{ 0.3535534 };
    const double hit_t_actual{ intersections[0].getT() };
    EXPECT_FLOAT_EQ(hit_t_actual, hit_t_expected);
}

// Tests ray intersections with a bounded, capped cone
TEST(GraphicsCone, RayConeIntersectionsBoundedCapped)
{
    const gfx::Cone cone{ -0.5, 0.5, true };

    const std::vector<gfx::Vector4> origin_list{
            gfx::createPoint(0, 0, -5),
            gfx::createPoint(0, 0, -0.25),
            gfx::createPoint(0, 0, -0.25)
    };

    const std::vector<gfx::Vector4> direction_list{
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, 1, 1),
            gfx::createVector(0, 1, 0)
    };

    const std::vector<size_t> intersection_count_expected_list {
            0,
            2,
            4
    };

    ASSERT_TRUE(origin_list.size() == direction_list.size());
    ASSERT_TRUE(origin_list.size() == intersection_count_expected_list.size());

    for (int i = 0; i < origin_list.size(); ++i) {
        const gfx::Ray ray{ origin_list[i],
                            gfx::normalize(direction_list[i]) };

        std::vector<gfx::Intersection> intersections{ cone.getObjectIntersections(ray) };

        EXPECT_EQ(intersections.size(), intersection_count_expected_list[i]);
    }
}

// Tests finding the surface normal on a bounded, capped cone
TEST(GraphicsCone, GetSurfaceNormalUnbounded)
{
    const gfx::Cone cone{ -2, 2, true};    // Assume an unbounded unit cone centered at the origin

    const std::vector<gfx::Vector4> point_list{
            gfx::createPoint(1, 1, 1),
            gfx::createPoint(-1, -1, 0),
            gfx::createPoint(-0.5, 2, -0.5),
            gfx::createPoint(0.5, -2, 0.5)
    };

    const std::vector<gfx::Vector4> surface_normaL_local_output_list{
            gfx::createVector(1, -M_SQRT2, 1),
            gfx::createVector(-1, 1, 0),
            gfx::createVector(0, 1, 0),
            gfx::createVector(0, -1, 0),
    };

    ASSERT_TRUE(point_list.size() == surface_normaL_local_output_list.size());

    for (int i = 0; i < point_list.size(); ++i) {
        const gfx::Vector4 surface_normal_actual{ cone.getSurfaceNormalAt(point_list[i]) };
        const gfx::Vector4 surface_normal_expected{ gfx::normalize(surface_normaL_local_output_list[i]) };
        EXPECT_EQ(surface_normal_actual, surface_normal_expected);
    }
}

#pragma clang diagnostic pop