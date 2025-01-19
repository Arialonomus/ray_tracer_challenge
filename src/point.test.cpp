#include <pch.h>
#include "point.hpp"

// Tests the default constructor
TEST(RTPoint, DefaultConstructor)
{
    const Point pt;

    EXPECT_FLOAT_EQ(pt.x(), 0.0);
    EXPECT_FLOAT_EQ(pt.y(), 0.0);
    EXPECT_FLOAT_EQ(pt.z(), 0.0);
    EXPECT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the standard constructor
TEST(RTPoint, Constructor)
{
    const Point pt{ 4.0, -4.0, 3.0 };

    EXPECT_FLOAT_EQ(pt.x(), 4.0);
    EXPECT_FLOAT_EQ(pt.y(), -4.0);
    EXPECT_FLOAT_EQ(pt.z(), 3.0);
    EXPECT_FLOAT_EQ(pt.w(), 1.0);
}

TEST(RTPoint, CopyConstructor)
{
    const Point pt_src{ 4.0, -4.0, 3.0 };
    const Point pt_cpy{ pt_src };

    EXPECT_FLOAT_EQ(pt_cpy.x(), 4.0);
    EXPECT_FLOAT_EQ(pt_cpy.y(), -4.0);
    EXPECT_FLOAT_EQ(pt_cpy.z(), 3.0);
    EXPECT_FLOAT_EQ(pt_cpy.w(), 1.0);
}