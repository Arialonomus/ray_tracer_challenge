#include "gtest/gtest.h"
#include "cylinder.hpp"

#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"

// Tests the default constructor
TEST(GraphicsCylinder, DefaultConstructor)
{
    const gfx::Cylinder cylinder{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    ASSERT_EQ(cylinder.getTransform(), transform_expected);
    ASSERT_EQ(cylinder.getMaterial(), material_expected);
}

// Tests the standard constructor
TEST(GraphicsCylinder, StandardConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Cylinder cylinder{ gfx::createScalingMatrix(5), material_expected };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    ASSERT_EQ(cylinder.getTransform(), transform_expected);
    ASSERT_EQ(cylinder.getMaterial(), material_expected);
}

// Tests the standard constructor (with default material)
TEST(GraphicsCylinder, StandardConstructorDefaultMaterial)
{
    const gfx::Cylinder cylinder{ gfx::createScalingMatrix(5) };
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };

    ASSERT_EQ(cylinder.getTransform(), transform_expected);
    ASSERT_EQ(cylinder.getMaterial(), material_expected);
}

// Tests the standard constructor (with default transform)
TEST(GraphicsCylinder, StandardConstructorDefaultTransform)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Cylinder cylinder{ material_expected };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(cylinder.getTransform(), transform_expected);
    ASSERT_EQ(cylinder.getMaterial(), material_expected);
}

// Tests the copy constructor
TEST(GraphicsCylinder, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Cylinder cylinder_src{ transform_expected, material_expected };
    const gfx::Cylinder cylinder_cpy{ cylinder_src };

    ASSERT_EQ(cylinder_cpy.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_cpy.getMaterial(), material_expected);
}

// Tests the assignment operator
TEST(GraphicsCylinder, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
    const gfx::Cylinder cylinder_a{ transform_expected, material_expected };
    gfx::Cylinder cylinder_b{ };

    cylinder_b = cylinder_a;

    ASSERT_EQ(cylinder_b.getTransform(), transform_expected);
    ASSERT_EQ(cylinder_b.getMaterial(), material_expected);
}

// Tests the equality operator
TEST(GraphicsCylinder, EqualityOperator)
{
    const gfx::Cylinder cylinder_a{ gfx::createScalingMatrix(5) };
    const gfx::Cylinder cylinder_b{ gfx::createScalingMatrix(5) };

    ASSERT_TRUE(cylinder_a == cylinder_b);
}

// Tests the inequality operator
TEST(GraphicsCylinder, InequalityOperator)
{
    const gfx::Cylinder cylinder_a{ gfx::createScalingMatrix(5) };
    const gfx::Cylinder cylinder_b{ };

    ASSERT_TRUE(cylinder_a != cylinder_b);
}

// Tests a ray missing a cylinder
TEST(GraphicsCylinder, RayCylinderMisses)
{
    const gfx::Cylinder cylinder{ };

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
    const gfx::Cylinder cylinder{ };

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