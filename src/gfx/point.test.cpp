#include <pch.h>
#include "point.hpp"

// Tests the default constructor
TEST(GraphicsPoint, DefaultConstructor)
{
    const gfx::Point pt;

    EXPECT_FLOAT_EQ(pt.x(), 0.0);
    EXPECT_FLOAT_EQ(pt.y(), 0.0);
    EXPECT_FLOAT_EQ(pt.z(), 0.0);
    EXPECT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the standard constructor
TEST(GraphicsPoint, Constructor)
{
    const gfx::Point pt{ 4.0, -4.0, 3.0 };

    EXPECT_FLOAT_EQ(pt.x(), 4.0);
    EXPECT_FLOAT_EQ(pt.y(), -4.0);
    EXPECT_FLOAT_EQ(pt.z(), 3.0);
    EXPECT_FLOAT_EQ(pt.w(), 1.0);
}

TEST(GraphicsPoint, CopyConstructor)
{
    const gfx::Point pt_src{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_cpy{ pt_src };

    EXPECT_FLOAT_EQ(pt_cpy.x(), 4.0);
    EXPECT_FLOAT_EQ(pt_cpy.y(), -4.0);
    EXPECT_FLOAT_EQ(pt_cpy.z(), 3.0);
    EXPECT_FLOAT_EQ(pt_cpy.w(), 1.0);
}

TEST(GraphicsPoint, ComparisonOperator)
{
    const gfx::Point pt_a{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_b{ 4.0, -4.0, 3.0 };

    EXPECT_TRUE(pt_a == pt_b);
}

TEST(GraphicsPoint, InequalityOperator)
{
    const gfx::Point pt_a{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_b{ 0.0, 5.0, -2.0 };

    EXPECT_TRUE(pt_a != pt_b);
}