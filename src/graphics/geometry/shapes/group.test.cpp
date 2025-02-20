#include "gtest/gtest.h"
#include "group.hpp"

#include "transform.hpp"
#include "sphere.hpp"

// Tests the default constructor
TEST(GraphicsGroup, DefaultConstructor)
{
    const gfx::Group group{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(group.getTransform(), transform_expected);
    ASSERT_TRUE(group.isEmpty());
}

// Tests the transform-only constructor
TEST(GraphicsGroup, TransformOnlyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Group group{ transform_expected };

    ASSERT_EQ(group.getTransform(), transform_expected);
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

    ASSERT_EQ(group_a.getTransform(), transform_expected);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(1)), sphere_b);

    // Test building from object pointers
    const std::shared_ptr<gfx::Sphere> sphere_a_ptr{ std::make_shared<gfx::Sphere>(sphere_a) };
    const std::shared_ptr<gfx::Sphere> sphere_b_ptr{ std::make_shared<gfx::Sphere>(sphere_b) };

    const gfx::Group group_b{ sphere_a_ptr, sphere_b_ptr };

    ASSERT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
}

// Tests the standard constructor
TEST(GraphicsGroup, StandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    // Test building directly from objects
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };

    ASSERT_EQ(group_a.getTransform(), transform_expected);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_a.getChildAt(1)), sphere_b);

    // Test building from object pointers
    const std::shared_ptr<gfx::Sphere> sphere_a_ptr{ std::make_shared<gfx::Sphere>(sphere_a) };
    const std::shared_ptr<gfx::Sphere> sphere_b_ptr{ std::make_shared<gfx::Sphere>(sphere_b) };

    const gfx::Group group_b{ transform_expected, sphere_a_ptr, sphere_b_ptr };

    ASSERT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
}

// Tests the copy constructor
TEST(GraphicsGroup, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_src{ transform_expected, sphere_a, sphere_b };
    const gfx::Group group_cpy{ group_src };

    ASSERT_EQ(group_cpy.getTransform(), transform_expected);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_cpy.getChildAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_cpy.getChildAt(1)), sphere_b);
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

    ASSERT_EQ(group_b.getTransform(), transform_expected);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(group_b.getChildAt(1)), sphere_b);
}

// Tests the equality operator
TEST(GraphicsGroup, EqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };
    gfx::Group group_b{ group_a };

    ASSERT_TRUE(group_a == group_b);
}

// Tests the inequality operator
TEST(GraphicsGroup, InequalityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Group group_a{ transform_expected, sphere_a, sphere_b };
    const gfx::Group group_b{ };

    ASSERT_TRUE(group_a != group_b);
}