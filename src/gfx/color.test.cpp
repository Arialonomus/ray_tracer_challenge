
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


// Tests color addition with the addition operator
TEST(GraphicsColor, ColorAdditionOperator)
{
    const gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    const gfx::Color clr_c = clr_a + clr_b;

    EXPECT_FLOAT_EQ(clr_c.r(), 1.6);
    EXPECT_FLOAT_EQ(clr_c.g(), 0.7);
    EXPECT_FLOAT_EQ(clr_c.b(), 1.0);
}

// Tests color addition with the addition shorthand operator
TEST(GraphicsColor, ColorAdditionShorthandOperator)
{
    gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    clr_a += clr_b;

    EXPECT_FLOAT_EQ(clr_a.r(), 1.6);
    EXPECT_FLOAT_EQ(clr_a.g(), 0.7);
    EXPECT_FLOAT_EQ(clr_a.b(), 1.0);
}

// Tests color subtraction with the subtraction operator
TEST(GraphicsColor, ColorSubtractionOperator)
{
    const gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    const gfx::Color clr_c = clr_a - clr_b;

    EXPECT_FLOAT_EQ(clr_c.r(), 0.2);
    EXPECT_FLOAT_EQ(clr_c.g(), 0.5);
    EXPECT_FLOAT_EQ(clr_c.b(), 0.5);
}

// Tests color subtraction with the subtraction shorthand operator
TEST(GraphicsColor, ColorSubtractionShorthandOperator)
{
    gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    clr_a -= clr_b;

    EXPECT_FLOAT_EQ(clr_a.r(), 0.2);
    EXPECT_FLOAT_EQ(clr_a.g(), 0.5);
    EXPECT_FLOAT_EQ(clr_a.b(), 0.5);
}

// Tests color scalar multiplication with the multiplication operator
TEST(GraphicsColor, ColorScalarMultiplicationOperator)
{
    const gfx::Color clr{ 0.2, 0.3, 0.4 };
    constexpr float scalar = 2.0;

    const gfx::Color clr_scaled = clr * scalar;

    EXPECT_FLOAT_EQ(clr_scaled.r(), 0.4);
    EXPECT_FLOAT_EQ(clr_scaled.g(), 0.6);
    EXPECT_FLOAT_EQ(clr_scaled.b(), 0.8);
}

// Tests color scalar multiplication with the multiplication shorthand operator
TEST(GraphicsColor, ColorScalarMultiplicationShorthandOperator)
{
    gfx::Color clr{ 0.2, 0.3, 0.4 };
    constexpr float scalar = 2.0;

    clr *= scalar;

    EXPECT_FLOAT_EQ(clr.r(), 0.4);
    EXPECT_FLOAT_EQ(clr.g(), 0.6);
    EXPECT_FLOAT_EQ(clr.b(), 0.8);
}
