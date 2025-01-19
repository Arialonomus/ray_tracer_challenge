#include <pch.h>
#include "vector.hpp"

// Tests the default constructor
TEST(GraphicsVector, DefaultConstructor)
{
    const gfx::Vector vec;

    EXPECT_FLOAT_EQ(vec.x(), 0.0);
    EXPECT_FLOAT_EQ(vec.y(), 0.0);
    EXPECT_FLOAT_EQ(vec.z(), 0.0);
    EXPECT_FLOAT_EQ(vec.w(), 0.0);
}

// Tests the standard constructor
TEST(GraphicsVector, Constructor)
{
    const gfx::Vector vec{ 4.0, -4.0, 3.0 };

    EXPECT_FLOAT_EQ(vec.x(), 4.0);
    EXPECT_FLOAT_EQ(vec.y(), -4.0);
    EXPECT_FLOAT_EQ(vec.z(), 3.0);
    EXPECT_FLOAT_EQ(vec.w(), 0.0);
}

TEST(GraphicsVector, CopyConstructor)
{
    const gfx::Vector vec_src{ 4.0, -4.0, 3.0 };
    const gfx::Vector vec_cpy{ vec_src };

    EXPECT_FLOAT_EQ(vec_cpy.x(), 4.0);
    EXPECT_FLOAT_EQ(vec_cpy.y(), -4.0);
    EXPECT_FLOAT_EQ(vec_cpy.z(), 3.0);
    EXPECT_FLOAT_EQ(vec_cpy.w(), 0.0);
}

TEST(GraphicsVector, ComparisonOperator)
{
    const gfx::Vector vec_a{ 4.0, -4.0, 3.0 };
    const gfx::Vector vec_b{ 4.0, -4.0, 3.0 };

    EXPECT_TRUE(vec_a == vec_b);
}

TEST(GraphicsVector, InequalityOperator)
{
    const gfx::Vector vec_a{ 4.0, -4.0, 3.0 };
    const gfx::Vector vec_b{ -1.0, -5.0, 0.0 };

    EXPECT_TRUE(vec_a != vec_b);
}