#include <pch.h>
#include <cmath>
#include "vector4.hpp"

// Tests the default constructor
TEST(GraphicsVector4, DefaultConstructor)
{
    const gfx::Vector4 vec;

    ASSERT_FLOAT_EQ(vec.x(), 0.0);
    ASSERT_FLOAT_EQ(vec.y(), 0.0);
    ASSERT_FLOAT_EQ(vec.z(), 0.0);
    ASSERT_FLOAT_EQ(vec.w(), 0.0);
}

// Tests the standard constructor
TEST(GraphicsVector4, StandardConstructor)
{
    const gfx::Vector4 vec{ 4.0, -4.0, 3.0, 0.5 };

    ASSERT_FLOAT_EQ(vec.x(), 4.0);
    ASSERT_FLOAT_EQ(vec.y(), -4.0);
    ASSERT_FLOAT_EQ(vec.z(), 3.0);
    ASSERT_FLOAT_EQ(vec.w(), 0.5);
}

// Tests the copy constructor
TEST(GraphicsVector4, CopyConstructor)
{
    const gfx::Vector4 vec_src{ 4.0, -4.0, 3.0, 1.5 };
    const gfx::Vector4 vec_cpy{ vec_src };

    ASSERT_FLOAT_EQ(vec_cpy.x(), 4.0);
    ASSERT_FLOAT_EQ(vec_cpy.y(), -4.0);
    ASSERT_FLOAT_EQ(vec_cpy.z(), 3.0);
    ASSERT_FLOAT_EQ(vec_cpy.w(), 1.5);
}

// Tests the assignment operator
TEST(GraphicsVector4, AssignmentOperator)
{
    gfx::Vector4 vec_a{ 1.0, 2.0, 3.0, 2.0 };
    const gfx::Vector4 vec_b{ 17.0, -3.5, 1.2, 3.7 };

    vec_a = vec_b;

    ASSERT_FLOAT_EQ(vec_a.x(), 17.0);
    ASSERT_FLOAT_EQ(vec_a.y(), -3.5);
    ASSERT_FLOAT_EQ(vec_a.z(), 1.2);
    ASSERT_FLOAT_EQ(vec_a.w(), 3.7);
}

// Tests the vector factory function
TEST(GraphicsVector4, VectorFactory)
{
    const gfx::Vector4 vec = gfx::vector(4.0, -4.0, 3.0);

    ASSERT_FLOAT_EQ(vec.x(), 4.0);
    ASSERT_FLOAT_EQ(vec.y(), -4.0);
    ASSERT_FLOAT_EQ(vec.z(), 3.0);
    ASSERT_FLOAT_EQ(vec.w(), 0.0);
}

// Tests the point factory function
TEST(GraphicsVector4, PointFactory)
{
    const gfx::Vector4 vec = gfx::point(4.0, -4.0, 3.0);

    ASSERT_FLOAT_EQ(vec.x(), 4.0);
    ASSERT_FLOAT_EQ(vec.y(), -4.0);
    ASSERT_FLOAT_EQ(vec.z(), 3.0);
    ASSERT_FLOAT_EQ(vec.w(), 1.0);
}

// Tests the comparison operator
TEST(GraphicsVector4, ComparisonOperator)
{
    const gfx::Vector4 vec_a{ 4.0, -4.0, 3.0, 0.0 };
    const gfx::Vector4 vec_b{ 4.0, -4.0, 3.0, 0.0 };

    EXPECT_TRUE(vec_a == vec_b);
}

// Tests the inequality operator
TEST(GraphicsVector4, InequalityOperator)
{
    const gfx::Vector4 vec_a{ 4.0, -4.0, 3.0, 0.0 };
    const gfx::Vector4 vec_b{ -1.0, -5.0, 0.0, 0.0 };

    EXPECT_TRUE(vec_a != vec_b);
}

// Tests vector-vector addition with the addition operator
TEST(GraphicsVector4, AdditionOperator)
{
    const gfx::Vector4 vec_a{ 1.0, 2.0, -3.0, 0.0 };
    const gfx::Vector4 vec_b{ 5.0, -4.5, 7.1, 1.6 };

    const gfx::Vector4 vec_c = vec_a + vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_c.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_c.z(), 4.1);
    EXPECT_FLOAT_EQ(vec_c.w(), 1.6);
}

// Tests vector-vector addition with the shorthand addition operator
TEST(GraphicsVector4, AdditionShorthandOperator)
{
    gfx::Vector4 vec_a{ 1.0, 2.0, -3.0, 0.0 };
    const gfx::Vector4 vec_b{ 5.0, -4.5, 7.1, 1.6 };

    vec_a += vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_a.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_a.z(), 4.1);
    EXPECT_FLOAT_EQ(vec_a.w(), 1.6);
}

// Tests the subtraction operator
TEST(GraphicsVector4, SubtractionOperator)
{
    const gfx::Vector4 vec_a{ 1.0, 2.0, -3.0, 0.0 };
    const gfx::Vector4 vec_b{ 5.0, -4.5, 7.1, 1.6 };

    const gfx::Vector4 vec_c = vec_a - vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), -4.0);
    EXPECT_FLOAT_EQ(vec_c.y(), 6.5);
    EXPECT_FLOAT_EQ(vec_c.z(), -10.1);
    EXPECT_FLOAT_EQ(vec_c.w(), -1.6);
}

// Tests the shorthand subtraction operator
TEST(GraphicsVector4, SubtractionShorthandOperator)
{
    gfx::Vector4 vec_a{ 1.0, 2.0, -3.0, 0.0 };
    const gfx::Vector4 vec_b{ 5.0, -4.5, 7.1, 1.6 };

    vec_a -= vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), -4.0);
    EXPECT_FLOAT_EQ(vec_a.y(), 6.5);
    EXPECT_FLOAT_EQ(vec_a.z(), -10.1);
    EXPECT_FLOAT_EQ(vec_a.w(), -1.6);
}

// Tests subtraction from the zero vector
TEST(GraphicsVector4, SubtractionFromZeroVector)
{
    const gfx::Vector4 vec_zero{ 0.0, 0.0, 0.0, 0.0 };
    const gfx::Vector4 vec{ 1.0, 2.0, -3.0, -4.0 };

    const gfx::Vector4 vec_neg = vec_zero - vec;

    EXPECT_FLOAT_EQ(vec_neg.x(), -1.0);
    EXPECT_FLOAT_EQ(vec_neg.y(), -2.0);
    EXPECT_FLOAT_EQ(vec_neg.z(), 3.0);
    EXPECT_FLOAT_EQ(vec_neg.w(), 4.0);
}

// Tests unary negation operator
TEST(GraphicsVector4, NegationOperator)
{
    const gfx::Vector4 vec_a{ 1.0, -2.0, 3.0, -4.0 };

    const gfx::Vector4 vec_b = -vec_a;

    EXPECT_FLOAT_EQ(vec_b.x(), -1.0);
    EXPECT_FLOAT_EQ(vec_b.y(), 2.0);
    EXPECT_FLOAT_EQ(vec_b.z(), -3.0);
    EXPECT_FLOAT_EQ(vec_b.w(), 4.0);
}

// Tests scalar multiplication operator and shows commutativity
TEST(GraphicsVector4, ScalarMultplication)
{
    const gfx::Vector4 vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 3.5;

    const gfx::Vector4 vec_scaled_l = vec * scalar;

    EXPECT_FLOAT_EQ(vec_scaled_l.x(), 3.5);
    EXPECT_FLOAT_EQ(vec_scaled_l.y(), -7.0);
    EXPECT_FLOAT_EQ(vec_scaled_l.z(), 10.5);
    EXPECT_FLOAT_EQ(vec_scaled_l.w(), -14.0);

    const gfx::Vector4 vec_scaled_r = scalar * vec;

    EXPECT_FLOAT_EQ(vec_scaled_r.x(), 3.5);
    EXPECT_FLOAT_EQ(vec_scaled_r.y(), -7.0);
    EXPECT_FLOAT_EQ(vec_scaled_r.z(), 10.5);
    EXPECT_FLOAT_EQ(vec_scaled_r.w(), -14.0);
}

// Tests scalar multiplication using the shorthand multiplication operator
TEST(GraphicsVector4, ScalarMultplicationShorthand)
{
    gfx::Vector4 vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 3.5;

    vec *= scalar;

    EXPECT_FLOAT_EQ(vec.x(), 3.5);
    EXPECT_FLOAT_EQ(vec.y(), -7.0);
    EXPECT_FLOAT_EQ(vec.z(), 10.5);
    EXPECT_FLOAT_EQ(vec.w(), -14.0);
}

// Tests scalar multiplication by a fraction
TEST(GraphicsVector4, ScalarMultplicationFraction)
{
    const gfx::Vector4 vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 0.5;

    const gfx::Vector4 vec_scaled = vec * scalar;

    EXPECT_FLOAT_EQ(vec_scaled.x(), 0.5);
    EXPECT_FLOAT_EQ(vec_scaled.y(), -1.0);
    EXPECT_FLOAT_EQ(vec_scaled.z(), 1.5);
    EXPECT_FLOAT_EQ(vec_scaled.w(), -2.0);
}

// Tests scalar division using the division operator
TEST(GraphicsVector4, ScalarDivision)
{
    const gfx::Vector4 vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 2.0;

    const gfx::Vector4 vec_scaled = vec / scalar;

    EXPECT_FLOAT_EQ(vec_scaled.x(), 0.5);
    EXPECT_FLOAT_EQ(vec_scaled.y(), -1.0);
    EXPECT_FLOAT_EQ(vec_scaled.z(), 1.5);
    EXPECT_FLOAT_EQ(vec_scaled.w(), -2.0);
}

// Tests scalar division using the shorthand division operator
TEST(GraphicsVector4, ScalarDivisionShorthand)
{
    gfx::Vector4 vec{ 1.0, -2.0, 3.0, -4.0 };
    constexpr float scalar = 2.0;

    vec /= scalar;

    EXPECT_FLOAT_EQ(vec.x(), 0.5);
    EXPECT_FLOAT_EQ(vec.y(), -1.0);
    EXPECT_FLOAT_EQ(vec.z(), 1.5);
    EXPECT_FLOAT_EQ(vec.w(), -2.0);
}

// Tests the magnitude member function
TEST(GraphicsVector4, Magnitude)
{
    const gfx::Vector4 vec_a{ 0.0, 1.0, 0.0, 0.0 };
    const gfx::Vector4 vec_b{ 0.0, 0.0, 1.0, 0.0 };
    const gfx::Vector4 vec_c{ 1.0, 2.0, 3.0, 0.0 };
    const gfx::Vector4 vec_d{ -1.0, -2.0, -3.0, 0.0 };

    ASSERT_FLOAT_EQ(vec_a.magnitude(), 1.0);
    ASSERT_FLOAT_EQ(vec_b.magnitude(), 1.0);
    ASSERT_FLOAT_EQ(vec_c.magnitude(), std::sqrt(14));
    ASSERT_FLOAT_EQ(vec_d.magnitude(), std::sqrt(14));
}

// Tests the normalize function for vectors
TEST(GraphicsVector4, Normalize)
{
    const gfx::Vector4 vec_a{ 4.0, 0.0, 0.0, 0.0 };
    const gfx::Vector4 vec_b{ 1.0, 2.0, 3.0, 0.0 };

    const gfx::Vector4 vec_a_norm = normalize(vec_a);

    EXPECT_FLOAT_EQ(vec_a_norm.x(), 1.0);
    EXPECT_FLOAT_EQ(vec_a_norm.y(), 0.0);
    EXPECT_FLOAT_EQ(vec_a_norm.z(), 0.0);
    EXPECT_FLOAT_EQ(vec_a_norm.w(), 0.0);

    const gfx::Vector4 vec_b_norm = normalize(vec_b);

    EXPECT_FLOAT_EQ(vec_b_norm.x(), 1.0 / std::sqrt(14));
    EXPECT_FLOAT_EQ(vec_b_norm.y(), 2.0 / std::sqrt(14));
    EXPECT_FLOAT_EQ(vec_b_norm.z(), 3.0 / std::sqrt(14));
    EXPECT_FLOAT_EQ(vec_b_norm.w(), 0.0);
}

// Tests the dot product function for vectors, and shows commutativity
TEST(GraphicsVector4, DotProduct)
{
    const gfx::Vector4 vec_a{ 1.0, 2.0, 3.0, 0.0 };
    const gfx::Vector4 vec_b{ 2.0, 3.0, 4.0, 0.0 };

    const float dot_l = dotProduct(vec_a, vec_b);
    const float dot_r = dotProduct(vec_b, vec_a);

    EXPECT_FLOAT_EQ(dot_l, 20.0);
    EXPECT_FLOAT_EQ(dot_r, 20.0);
}

// Tests the vector cross product member function
TEST(GraphicsVector4, CrossProduct)
{
    const gfx::Vector4 vec_a{ 1.0, 2.0, 3.0, 0.0 };
    const gfx::Vector4 vec_b{ 2.0, 3.0, 4.0, 0.0 };

    const gfx::Vector4 cross_a = vec_a.crossProduct(vec_b);

    EXPECT_FLOAT_EQ(cross_a.x(), -1.0);
    EXPECT_FLOAT_EQ(cross_a.y(), 2.0);
    EXPECT_FLOAT_EQ(cross_a.z(), -1.0);
    EXPECT_FLOAT_EQ(cross_a.w(), 0.0);

    const gfx::Vector4 cross_b = vec_b.crossProduct(vec_a);

    EXPECT_FLOAT_EQ(cross_b.x(), 1.0);
    EXPECT_FLOAT_EQ(cross_b.y(), -2.0);
    EXPECT_FLOAT_EQ(cross_b.z(), 1.0);
    EXPECT_FLOAT_EQ(cross_b.w(), 0.0);
}