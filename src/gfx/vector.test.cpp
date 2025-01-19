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

// Tests the copy constructor
TEST(GraphicsVector, CopyConstructor)
{
    const gfx::Vector vec_src{ 4.0, -4.0, 3.0 };
    const gfx::Vector vec_cpy{ vec_src };

    EXPECT_FLOAT_EQ(vec_cpy.x(), 4.0);
    EXPECT_FLOAT_EQ(vec_cpy.y(), -4.0);
    EXPECT_FLOAT_EQ(vec_cpy.z(), 3.0);
    EXPECT_FLOAT_EQ(vec_cpy.w(), 0.0);
}

// Tests the assignment operator
TEST(GraphicsVector, AssignmentOperator)
{
    gfx::Vector vec_a{ 1.0, 2.0, 3.0 };
    const gfx::Vector vec_b{ 17.0, -3.5, 1.2 };

    vec_a = vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), 17.0);
    EXPECT_FLOAT_EQ(vec_a.y(), -3.5);
    EXPECT_FLOAT_EQ(vec_a.z(), 1.2);
    EXPECT_FLOAT_EQ(vec_a.w(), 0.0);
}

// Tests the comparison operator
TEST(GraphicsVector, ComparisonOperator)
{
    const gfx::Vector vec_a{ 4.0, -4.0, 3.0 };
    const gfx::Vector vec_b{ 4.0, -4.0, 3.0 };

    EXPECT_TRUE(vec_a == vec_b);
}

// Tests the inequality operator
TEST(GraphicsVector, InequalityOperator)
{
    const gfx::Vector vec_a{ 4.0, -4.0, 3.0 };
    const gfx::Vector vec_b{ -1.0, -5.0, 0.0 };

    EXPECT_TRUE(vec_a != vec_b);
}

// Tests vector-vector addition with the addition operator
TEST(GraphicsVector, VectorVectorAddition)
{
    const gfx::Vector vec_a{ 1.0, 2.0, -3.0 };
    const gfx::Vector vec_b{ 5.0, -4.5, 7.1 };

    const gfx::Vector vec_c = vec_a + vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_c.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_c.z(), 4.1);
    EXPECT_FLOAT_EQ(vec_c.w(), 0.0);
}