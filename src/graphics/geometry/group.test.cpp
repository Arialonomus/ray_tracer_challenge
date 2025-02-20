#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "group.hpp"

#include <cmath>
#include <vector>

#include "transform.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the default constructor
TEST(GraphicsGroup, DefaultConstructor)
{
    const gfx::Group group{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    EXPECT_EQ(group.getTransform(), transform_expected);
    ASSERT_TRUE(group.isEmpty());
}

// Tests the transform-only constructor
TEST(GraphicsGroup, TransformOnlyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Group group{ transform_expected };

    EXPECT_EQ(group.getTransform(), transform_expected);
    ASSERT_TRUE(group.isEmpty());
}

// Tests the object list constructor
TEST(GraphicsGroup, ObjectListConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    // Test building directly from objects
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ sphere_a, sphere_b };

    EXPECT_EQ(group_a.getTransform(), transform_expected);
    ASSERT_FALSE(group_a.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_a.getChildAt(0).getParent(), &group_a);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_a.getChildAt(1).getParent(), &group_a);

    // Test building from object pointers
    const std::shared_ptr<gfx::Sphere> sphere_a_ptr{ std::make_shared<gfx::Sphere>(sphere_a) };
    const std::shared_ptr<gfx::Sphere> sphere_b_ptr{ std::make_shared<gfx::Sphere>(sphere_b) };

    const gfx::Group group_b{ sphere_a_ptr, sphere_b_ptr };

    ASSERT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_FALSE(group_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_b.getChildAt(0).getParent(), &group_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_b.getChildAt(1).getParent(), &group_b);
}

// Tests the standard constructor
TEST(GraphicsGroup, StandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    // Test building directly from objects
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };

    EXPECT_EQ(group_a.getTransform(), transform_expected);
    ASSERT_FALSE(group_a.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_a.getChildAt(0).getParent(), &group_a);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_a.getChildAt(1).getParent(), &group_a);

    // Test building from object pointers
    const std::shared_ptr<gfx::Sphere> sphere_a_ptr{ std::make_shared<gfx::Sphere>(sphere_a) };
    const std::shared_ptr<gfx::Sphere> sphere_b_ptr{ std::make_shared<gfx::Sphere>(sphere_b) };

    const gfx::Group group_b{ transform_expected, sphere_a_ptr, sphere_b_ptr };

    EXPECT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_FALSE(group_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_b.getChildAt(0).getParent(), &group_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_b.getChildAt(1).getParent(), &group_b);
}

// Tests the copy constructor
TEST(GraphicsGroup, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_src{ transform_expected, sphere_a, sphere_b };
    const gfx::Group group_cpy{ group_src };

    EXPECT_EQ(group_cpy.getTransform(), transform_expected);
    ASSERT_FALSE(group_cpy.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_cpy.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_cpy.getChildAt(0).getParent(), &group_cpy);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_cpy.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_cpy.getChildAt(1).getParent(), &group_cpy);
}

// Tests the move constructor
TEST(GraphicsGroup, MoveConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_src{ transform_expected, sphere_a, sphere_b };
    const gfx::Group group_moved{ std::move(group_src) };

    EXPECT_EQ(group_moved.getTransform(), transform_expected);
    ASSERT_FALSE(group_moved.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_moved.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_moved.getChildAt(0).getParent(), &group_moved);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_moved.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_moved.getChildAt(1).getParent(), &group_moved);
}

// Tests the assignment operator
TEST(GraphicsGroup, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };
    gfx::Group group_b{ };

    group_b = group_a;

    EXPECT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_FALSE(group_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_b.getChildAt(0).getParent(), &group_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_b.getChildAt(1).getParent(), &group_b);
}

// Tests the move assignment operator
TEST(GraphicsGroup, MoveAssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };
    gfx::Group group_b{ };

    group_b = std::move(group_a);

    EXPECT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_FALSE(group_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(group_b.getChildAt(0).getParent(), &group_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(group_b.getChildAt(1).getParent(), &group_b);
}

// Tests the equality operator
TEST(GraphicsGroup, EqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };
    gfx::Group group_b{ group_a };

    EXPECT_TRUE(group_a == group_b);
}

// Tests the inequality operator
TEST(GraphicsGroup, InequalityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };
    const gfx::Group group_b{ };

    EXPECT_TRUE(group_a != group_b);
}

// Tests adding children to the group
TEST(GraphicsGroup, AddChild)
{
    gfx::Group group{ };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };

    // Add object directly
    group.addChild(sphere_a);

    // Add object via shared pointer
    group.addChild(std::make_shared<gfx::Sphere>(sphere_b));

    ASSERT_FALSE(group.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group.getChildAt(0)), sphere_a);
    EXPECT_EQ(group.getChildAt(0).getParent(), &group);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(group.getChildAt(1)), sphere_b);
    EXPECT_EQ(group.getChildAt(1).getParent(), &group);
}

// Tests intersecting a ray with an empty group
TEST(GraphicsGroup, RayEmptyGroupIntersection)
{
    const gfx::Group group{ };
    const gfx::Ray ray{ 0, 0, 0,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> intersections{ group.getObjectIntersections(ray) };

    EXPECT_TRUE(intersections.empty());
}

// Tests intersecting a ray with a non-empty group
TEST(GraphicsGroup, RayGroupIntersection)
{
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ gfx::createTranslationMatrix(0, 0, -3) };
    const gfx::Sphere sphere_c{ gfx::createTranslationMatrix(5, 0, 0) };
    const gfx::Group group{ sphere_a, sphere_b, sphere_c };
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> intersections{ group.getObjectIntersections(ray) };

    ASSERT_EQ(intersections.size(), 4);
    EXPECT_EQ(intersections.at(0).getObject(), sphere_b);
    EXPECT_EQ(intersections.at(1).getObject(), sphere_b);
    EXPECT_EQ(intersections.at(2).getObject(), sphere_a);
    EXPECT_EQ(intersections.at(3).getObject(), sphere_a);
}

// Tests intersecting a ray with a non-empty group with a transformation applied
TEST(GraphicsGroup, RayTransformedGroupIntersection)
{
    const gfx::Sphere sphere{ gfx::createTranslationMatrix(5, 0, 0) };
    const gfx::Group group{ gfx::createScalingMatrix(2),
                            sphere };
    const gfx::Ray ray{ 10, 0, -10,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> intersections{ group.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
}

// Tests finding the normal on a child object
TEST(GraphicsGroup, GetSurfaceNormalChildObject)
{
    const std::shared_ptr<gfx::Sphere> sphere_ptr{
        std::make_shared<gfx::Sphere>(gfx::createTranslationMatrix(5, 0, 0))
    };
    const gfx::Group group_child{ gfx::createScalingMatrix(1, 2, 3), sphere_ptr };
    const gfx::Group group_parent{ gfx::createYRotationMatrix(M_PI_2), group_child };

    const gfx::Vector4 point{ gfx::createPoint(1.7321, 1.1547, -5.5774) };

    const gfx::Vector4 normal_expected{ gfx::createVector(0.285704, 0.428543, -0.857160) };
    const gfx::Vector4 normal_actual{ sphere_ptr->getSurfaceNormalAt(point) };

    EXPECT_EQ(normal_actual, normal_expected);
}

#pragma clang diagnostic pop