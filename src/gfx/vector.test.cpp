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

// Tests the homogeneous coordinate constructor
TEST(GraphicsVector, HomogeneousConstructor)
{
    const gfx::Vector vec{ 4.0, -4.0, 3.0, 0.5 };

    EXPECT_FLOAT_EQ(vec.x(), 4.0);
    EXPECT_FLOAT_EQ(vec.y(), -4.0);
    EXPECT_FLOAT_EQ(vec.z(), 3.0);
    EXPECT_FLOAT_EQ(vec.w(), 0.5);
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
TEST(GraphicsVector, VectorAdditionOperator)
{
    const gfx::Vector vec_a{ 1.0, 2.0, -3.0 };
    const gfx::Vector vec_b{ 5.0, -4.5, 7.1 };

    const gfx::Vector vec_c = vec_a + vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_c.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_c.z(), 4.1);
    EXPECT_FLOAT_EQ(vec_c.w(), 0.0);
}

// Tests vector-vector addition with the shorthand addition operator
TEST(GraphicsVector, VectorAdditionShorthandOperator)
{
    gfx::Vector vec_a{ 1.0, 2.0, -3.0 };
    const gfx::Vector vec_b{ 5.0, -4.5, 7.1 };

    vec_a += vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_a.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_a.z(), 4.1);
    EXPECT_FLOAT_EQ(vec_a.w(), 0.0);
}

// Tests vector-vector subtraction with the subtraction operator
TEST(GraphicsVector, VectorSubtractionOperator)
{
    const gfx::Vector vec_a{ 1.0, 2.0, -3.0 };
    const gfx::Vector vec_b{ 5.0, -4.5, 7.1 };

    const gfx::Vector vec_c = vec_a - vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), -4.0);
    EXPECT_FLOAT_EQ(vec_c.y(), 6.5);
    EXPECT_FLOAT_EQ(vec_c.z(), -10.1);
    EXPECT_FLOAT_EQ(vec_c.w(), 0.0);
}

// Tests vector-vector subtraction with the shorthand subtraction operator
TEST(GraphicsVector, VectorSubtractionShorthandOperator)
{
    gfx::Vector vec_a{ 1.0, 2.0, -3.0 };
    const gfx::Vector vec_b{ 5.0, -4.5, 7.1 };

    vec_a -= vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), -4.0);
    EXPECT_FLOAT_EQ(vec_a.y(), 6.5);
    EXPECT_FLOAT_EQ(vec_a.z(), -10.1);
    EXPECT_FLOAT_EQ(vec_a.w(), 0.0);
}

// Tests subtraction from the zero vector
TEST(GraphicsVector, SubtractionFromZeroVector)
{
    const gfx::Vector vec_zero{ 0.0, 0.0, 0.0 };
    const gfx::Vector vec{ 1.0, 2.0, -3.0 };

    const gfx::Vector vec_neg = vec_zero - vec;

    EXPECT_FLOAT_EQ(vec_neg.x(), -1.0);
    EXPECT_FLOAT_EQ(vec_neg.y(), -2.0);
    EXPECT_FLOAT_EQ(vec_neg.z(), 3.0);
    EXPECT_FLOAT_EQ(vec_neg.w(), 0.0);
}

// Tests unary negation operator
TEST(GraphicsVector, NegationOperator)
{
    const gfx::Vector vec_a{ 1.0, -2.0, 3.0, -4.0 };

    const gfx::Vector vec_b = -vec_a;

    EXPECT_FLOAT_EQ(vec_b.x(), -1.0);
    EXPECT_FLOAT_EQ(vec_b.y(), 2.0);
    EXPECT_FLOAT_EQ(vec_b.z(), -3.0);
    EXPECT_FLOAT_EQ(vec_b.w(), 4.0);
}

// Tests scalar multiplication when the vector is the left-hand operand
TEST(GraphicsVector, ScalarMultplicationLeft)
{
    const gfx::Vector vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 3.5;

    const gfx::Vector vec_scaled = vec * scalar;

    EXPECT_FLOAT_EQ(vec_scaled.x(), 3.5);
    EXPECT_FLOAT_EQ(vec_scaled.y(), -7.0);
    EXPECT_FLOAT_EQ(vec_scaled.z(), 10.5);
    EXPECT_FLOAT_EQ(vec_scaled.w(), -14.0);
}

// Tests scalar multiplication when the vector is the right-hand operand
TEST(GraphicsVector, ScalarMultplicationRight)
{
    const gfx::Vector vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 3.5;

    const gfx::Vector vec_scaled = scalar * vec;

    EXPECT_FLOAT_EQ(vec_scaled.x(), 3.5);
    EXPECT_FLOAT_EQ(vec_scaled.y(), -7.0);
    EXPECT_FLOAT_EQ(vec_scaled.z(), 10.5);
    EXPECT_FLOAT_EQ(vec_scaled.w(), -14.0);
}

// Tests scalar multiplication using the shorthand multiplication operator
TEST(GraphicsVector, ScalarMultplicationShorthand)
{
    gfx::Vector vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 3.5;

    vec *= scalar;

    EXPECT_FLOAT_EQ(vec.x(), 3.5);
    EXPECT_FLOAT_EQ(vec.y(), -7.0);
    EXPECT_FLOAT_EQ(vec.z(), 10.5);
    EXPECT_FLOAT_EQ(vec.w(), -14.0);
}