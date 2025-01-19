#include <pch.h>
#include "point.hpp"

// Tests the default constructor
TEST(GraphicsPoint, DefaultConstructor)
{
    const gfx::Point pt;

    ASSERT_FLOAT_EQ(pt.x(), 0.0);
    ASSERT_FLOAT_EQ(pt.y(), 0.0);
    ASSERT_FLOAT_EQ(pt.z(), 0.0);
    ASSERT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the standard constructor
TEST(GraphicsPoint, Constructor)
{
    const gfx::Point pt{ 4.0, -4.0, 3.0 };

    ASSERT_FLOAT_EQ(pt.x(), 4.0);
    ASSERT_FLOAT_EQ(pt.y(), -4.0);
    ASSERT_FLOAT_EQ(pt.z(), 3.0);
    ASSERT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the homogeneous coordinate constructor
TEST(GraphicsPoint, HomogeneousConstructor)
{
    const gfx::Point pt{ 4.0, -4.0, 3.0, 0.5 };

    ASSERT_FLOAT_EQ(pt.x(), 4.0);
    ASSERT_FLOAT_EQ(pt.y(), -4.0);
    ASSERT_FLOAT_EQ(pt.z(), 3.0);
    ASSERT_FLOAT_EQ(pt.w(), 0.5);
}


// Tests the copy constructor
TEST(GraphicsPoint, CopyConstructor)
{
    const gfx::Point pt_src{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_cpy{ pt_src };

    ASSERT_FLOAT_EQ(pt_cpy.x(), 4.0);
    ASSERT_FLOAT_EQ(pt_cpy.y(), -4.0);
    ASSERT_FLOAT_EQ(pt_cpy.z(), 3.0);
    ASSERT_FLOAT_EQ(pt_cpy.w(), 1.0);
}

// Tests the assignment operator
TEST(GraphicsVector, AssignmentOperator)
{
    gfx::Point pt_a{ 1.0, 2.0, 3.0 };
    const gfx::Point pt_b{ 17.0, -3.5, 1.2 };

    pt_a = pt_b;

    ASSERT_FLOAT_EQ(pt_a.x(), 17.0);
    ASSERT_FLOAT_EQ(pt_a.y(), -3.5);
    ASSERT_FLOAT_EQ(pt_a.z(), 1.2);
    ASSERT_FLOAT_EQ(pt_a.w(), 1.0);
}

// Tests the equality operator
TEST(GraphicsPoint, EqualityOperator)
{
    const gfx::Point pt_a{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_b{ 4.0, -4.0, 3.0 };

    EXPECT_TRUE(pt_a == pt_b);
}

// Tests the inequality operator
TEST(GraphicsPoint, InequalityOperator)
{
    const gfx::Point pt_a{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_b{ 0.0, 5.0, -2.0 };

    EXPECT_TRUE(pt_a != pt_b);
}