#include "gtest/gtest.h"
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
    gfx::Color clr_a{ };
    const gfx::Color clr_b{ -0.5, 0.4, 1.7 };

    clr_a = clr_b;

    ASSERT_FLOAT_EQ(clr_a.r(), -0.5);
    ASSERT_FLOAT_EQ(clr_a.g(), 0.4);
    ASSERT_FLOAT_EQ(clr_a.b(), 1.7);
}

// Tests the equality operator
TEST(GraphicsColor, EqualityOperator)
{
    const gfx::Color clr_a{ -0.5, 0.4, 1.7 };
    const gfx::Color clr_b{ -0.5, 0.4, 1.7 };

    EXPECT_TRUE(clr_a == clr_b);
}

// Tests the inequality operator
TEST(GraphicsColor, InequalityOperator)
{
    const gfx::Color clr_a{ 1.0, 2.0, 3.0 };
    const gfx::Color clr_b{ -0.5, 0.4, 1.7 };

    EXPECT_TRUE(clr_a != clr_b);
}

// Tests the color mutator
TEST(GraphicsColor, Mutator)
{
    gfx::Color color{ };
    const double r_expected{ 0.5 };
    const double g_expected{ 0.5 };
    const double b_expected{ 0.5 };

    color.setValues(r_expected, g_expected, b_expected);

    ASSERT_FLOAT_EQ(color.r(), r_expected);
    ASSERT_FLOAT_EQ(color.g(), g_expected);
    ASSERT_FLOAT_EQ(color.g(), b_expected);
}

// Tests color addition with the addition operator
TEST(GraphicsColor, AdditionOperator)
{
    const gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    const gfx::Color clr_c = clr_a + clr_b;

    EXPECT_FLOAT_EQ(clr_c.r(), 1.6);
    EXPECT_FLOAT_EQ(clr_c.g(), 0.7);
    EXPECT_FLOAT_EQ(clr_c.b(), 1.0);
}

// Tests color addition with the addition shorthand operator
TEST(GraphicsColor, AdditionShorthandOperator)
{
    gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    clr_a += clr_b;

    EXPECT_FLOAT_EQ(clr_a.r(), 1.6);
    EXPECT_FLOAT_EQ(clr_a.g(), 0.7);
    EXPECT_FLOAT_EQ(clr_a.b(), 1.0);
}

// Tests color subtraction with the subtraction operator
TEST(GraphicsColor, SubtractionOperator)
{
    const gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    const gfx::Color clr_c = clr_a - clr_b;

    EXPECT_FLOAT_EQ(clr_c.r(), 0.2);
    EXPECT_FLOAT_EQ(clr_c.g(), 0.5);
    EXPECT_FLOAT_EQ(clr_c.b(), 0.5);
}

// Tests color subtraction with the subtraction shorthand operator
TEST(GraphicsColor, SubtractionShorthandOperator)
{
    gfx::Color clr_a{ 0.9, 0.6, 0.75 };
    const gfx::Color clr_b{ 0.7, 0.1, 0.25 };

    clr_a -= clr_b;

    EXPECT_FLOAT_EQ(clr_a.r(), 0.2);
    EXPECT_FLOAT_EQ(clr_a.g(), 0.5);
    EXPECT_FLOAT_EQ(clr_a.b(), 0.5);
}

// Tests color scalar multiplication with the multiplication operator and shows commutativity
TEST(GraphicsColor, ScalarMultiplicationOperator)
{
    const gfx::Color clr{ 0.2, 0.3, 0.4 };
    constexpr double scalar = 2.0;

    const gfx::Color clr_scaled_l = clr * scalar;

    EXPECT_FLOAT_EQ(clr_scaled_l.r(), 0.4);
    EXPECT_FLOAT_EQ(clr_scaled_l.g(), 0.6);
    EXPECT_FLOAT_EQ(clr_scaled_l.b(), 0.8);

    const gfx::Color clr_scaled_r = scalar * clr;

    EXPECT_FLOAT_EQ(clr_scaled_r.r(), 0.4);
    EXPECT_FLOAT_EQ(clr_scaled_r.g(), 0.6);
    EXPECT_FLOAT_EQ(clr_scaled_r.b(), 0.8);
}

// Tests color scalar multiplication with the multiplication shorthand operator
TEST(GraphicsColor, ScalarMultiplicationShorthandOperator)
{
    gfx::Color clr{ 0.2, 0.3, 0.4 };
    constexpr double scalar = 2.0;

    clr *= scalar;

    EXPECT_FLOAT_EQ(clr.r(), 0.4);
    EXPECT_FLOAT_EQ(clr.g(), 0.6);
    EXPECT_FLOAT_EQ(clr.b(), 0.8);
}

// Tests color multiplication (Hadamard product) with the multiplication operator and shows commutativity
TEST(GraphicsColor, MultiplicationOperator)
{
    const gfx::Color clr_a{ 1.0, 0.2, 0.4 };
    const gfx::Color clr_b{ 0.9, 1.0, 0.1 };

    const gfx::Color clr_product_l = clr_a * clr_b;

    EXPECT_FLOAT_EQ(clr_product_l.r(), 0.9);
    EXPECT_FLOAT_EQ(clr_product_l.g(), 0.2);
    EXPECT_FLOAT_EQ(clr_product_l.b(), 0.04);

    const gfx::Color clr_product_r = clr_b * clr_a;

    EXPECT_FLOAT_EQ(clr_product_r.r(), 0.9);
    EXPECT_FLOAT_EQ(clr_product_r.g(), 0.2);
    EXPECT_FLOAT_EQ(clr_product_r.b(), 0.04);
}

// Tests color multiplication (Hadamard product) with the multiplication shorthand operator
TEST(GraphicsColor, MultiplicationShorthandOperator)
{
    gfx::Color clr_a{ 1.0, 0.2, 0.4 };
    const gfx::Color clr_b{ 0.9, 1.0, 0.1 };

    clr_a *= clr_b;

    EXPECT_FLOAT_EQ(clr_a.r(), 0.9);
    EXPECT_FLOAT_EQ(clr_a.g(), 0.2);
    EXPECT_FLOAT_EQ(clr_a.b(), 0.04);
}
