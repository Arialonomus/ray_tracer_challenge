
#include <pch.h>
#include "color.hpp"

// Tests the default constructor
TEST(GraphicsColor, DefaultConstructor)
{
    const gfx::Color clr;

    ASSERT_FLOAT_EQ(clr.r(), 0.0);
    ASSERT_FLOAT_EQ(clr.g(), 0.0);
    ASSERT_FLOAT_EQ(clr.b(), 0.0);
}

// Tests the standard constructor
TEST(GraphicsColor, Constructor)
{
    const gfx::Color clr{ -0.5, 0.4, 1.7 };

    ASSERT_FLOAT_EQ(clr.r(), -0.5);
    ASSERT_FLOAT_EQ(clr.g(), 0.4);
    ASSERT_FLOAT_EQ(clr.b(), 1.7);
}

// Tests the copy constructor
TEST(GraphicsColor, CopyConstructor)
{
    const gfx::Color clr_src{ -0.5, 0.4, 1.7 };
    const gfx::Color clr_cpy{ clr_src };

    ASSERT_FLOAT_EQ(clr_cpy.r(), -0.5);
    ASSERT_FLOAT_EQ(clr_cpy.g(), 0.4);
    ASSERT_FLOAT_EQ(clr_cpy.b(), 1.7);
}

// Tests the assignment operator
TEST(GraphicsColor, AssignmentOperator)
{
    gfx::Color clr_a{ 1.0, 2.0, 3.0 };
    const gfx::Color clr_b{ -0.5, 0.4, 1.7 };

    clr_a = clr_b;

    ASSERT_FLOAT_EQ(clr_a.r(), -0.5);
    ASSERT_FLOAT_EQ(clr_a.g(), 0.4);
    ASSERT_FLOAT_EQ(clr_a.b(), 1.7);
}
