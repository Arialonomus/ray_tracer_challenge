#include "gtest/gtest.h"
#include "vector3.hpp"

#include <array>
#include <cmath>
#include <string>
#include <format>

#include "matrix3.hpp"

// Tests the default constructor
TEST(GraphicsVector3, DefaultConstructor)
{
    const gfx::Vector3 vec;

    EXPECT_FLOAT_EQ(vec.x(), 0.0);
    EXPECT_FLOAT_EQ(vec.y(), 0.0);
    EXPECT_FLOAT_EQ(vec.w(), 0.0);
}

// Tests the double list constructor
TEST(GraphicsVector3, FloatListConstructor)
{
    const gfx::Vector3 vec{ 4.0, -4.0, 0.5 };

    EXPECT_FLOAT_EQ(vec.x(), 4.0);
    EXPECT_FLOAT_EQ(vec.y(), -4.0);
    EXPECT_FLOAT_EQ(vec.w(), 0.5);
}

// Tests the span-based constructor
TEST(GraphicsVector3, SpanConstructor)
{
    const std::array<double, 3> vec_values{ 4.0, -4.0, 0.5 };
    const gfx::Vector3 vec{ vec_values };

    EXPECT_FLOAT_EQ(vec.x(), 4.0);
    EXPECT_FLOAT_EQ(vec.y(), -4.0);
    EXPECT_FLOAT_EQ(vec.w(), 0.5);
}

// Tests the copy constructor
TEST(GraphicsVector3, CopyConstructor)
{
    const gfx::Vector3 vec_src{ 4.0, -4.0, 1.5 };
    const gfx::Vector3 vec_cpy{ vec_src };

    EXPECT_FLOAT_EQ(vec_cpy.x(), 4.0);
    EXPECT_FLOAT_EQ(vec_cpy.y(), -4.0);
    EXPECT_FLOAT_EQ(vec_cpy.w(), 1.5);
}

// Tests the assignment operator
TEST(GraphicsVector3, AssignmentOperator)
{
    gfx::Vector3 vec_a{ };
    const gfx::Vector3 vec_b{ 17.0, -3.5, 3.7 };

    vec_a = vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), 17.0);
    EXPECT_FLOAT_EQ(vec_a.y(), -3.5);
    EXPECT_FLOAT_EQ(vec_a.w(), 3.7);
}

// Tests the comparison operator
TEST(GraphicsVector3, ComparisonOperator)
{
    const gfx::Vector3 vec_a{ 4.0, -4.0, 0.0 };
    const gfx::Vector3 vec_b{ 4.0, -4.0, 0.0 };

    EXPECT_TRUE(vec_a == vec_b);
}

// Tests the inequality operator
TEST(GraphicsVector3, InequalityOperator)
{
    const gfx::Vector3 vec_a{ 4.0, -4.0, 0.0 };
    const gfx::Vector3 vec_b{ -1.0, -5.0, 0.0 };

    EXPECT_TRUE(vec_a != vec_b);
}

// Tests vector-vector addition with the addition operator
TEST(GraphicsVector3, AdditionOperator)
{
    const gfx::Vector3 vec_a{ 1.0, 2.0, 0.0 };
    const gfx::Vector3 vec_b{ 5.0, -4.5, 1.0 };

    const gfx::Vector3 vec_c = vec_a + vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_c.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_c.w(), 1);
}

// Tests vector-vector addition with the shorthand addition operator
TEST(GraphicsVector3, AdditionShorthandOperator)
{
    gfx::Vector3 vec_a{ 1.0, 2.0,  0.0 };
    const gfx::Vector3 vec_b{ 5.0, -4.5, 1.0 };

    vec_a += vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), 6.0);
    EXPECT_FLOAT_EQ(vec_a.y(), -2.5);
    EXPECT_FLOAT_EQ(vec_a.w(), 1.0);
}

// Tests that adding two points throws an invalid_argument exception
TEST(GraphicsVector3, PointAdditionException)
{
    gfx::Vector3 point_a{ 1.0, 2.0, 1.0 };
    const gfx::Vector3 point_b{ 5.0, -4.5, 1.0 };

    // Test throwing with normal addition operator
    EXPECT_THROW({
        const gfx::Vector3 point_c{ point_a + point_b };
        }, std::invalid_argument);

    // Test throwing with addition shorthand operator
    EXPECT_THROW({
        point_a += point_b;
        }, std::invalid_argument);
}

// Tests the subtraction operator
TEST(GraphicsVector3, SubtractionOperator)
{
    const gfx::Vector3 vec_a{ 1.0, 2.0, 0.0 };
    const gfx::Vector3 vec_b{ 5.0, -4.5, 1.6 };

    const gfx::Vector3 vec_c = vec_a - vec_b;

    EXPECT_FLOAT_EQ(vec_c.x(), -4.0);
    EXPECT_FLOAT_EQ(vec_c.y(), 6.5);
    EXPECT_FLOAT_EQ(vec_c.w(), -1.6);
}

// Tests the shorthand subtraction operator
TEST(GraphicsVector3, SubtractionShorthandOperator)
{
    gfx::Vector3 vec_a{ 1.0, 2.0, 0.0 };
    const gfx::Vector3 vec_b{ 5.0, -4.5, 1.6 };

    vec_a -= vec_b;

    EXPECT_FLOAT_EQ(vec_a.x(), -4.0);
    EXPECT_FLOAT_EQ(vec_a.y(), 6.5);
    EXPECT_FLOAT_EQ(vec_a.w(), -1.6);
}

// Tests subtraction from the zero vector
TEST(GraphicsVector3, SubtractionFromZeroVector)
{
    const gfx::Vector3 vec_zero{ 0.0, 0.0, 0.0 };
    const gfx::Vector3 vec{ 1.0, 2.0, -3.0 };

    const gfx::Vector3 vec_neg = vec_zero - vec;

    EXPECT_FLOAT_EQ(vec_neg.x(), -1.0);
    EXPECT_FLOAT_EQ(vec_neg.y(), -2.0);
    EXPECT_FLOAT_EQ(vec_neg.w(), 3.0);
}

// Tests unary negation operator
TEST(GraphicsVector3, NegationOperator)
{
    const gfx::Vector3 vec_a{ 1.0, -2.0, 3.0 };

    const gfx::Vector3 vec_b = -vec_a;

    EXPECT_FLOAT_EQ(vec_b.x(), -1.0);
    EXPECT_FLOAT_EQ(vec_b.y(), 2.0);
    EXPECT_FLOAT_EQ(vec_b.w(), -3.0);
}

// Tests scalar multiplication operator and shows commutativity
TEST(GraphicsVector3, ScalarMultplication)
{
    const gfx::Vector3 vec{ 1.0, -2.0, 3.0 };
    constexpr double scalar = 3.5;

    const gfx::Vector3 vec_scaled_l = vec * scalar;

    EXPECT_FLOAT_EQ(vec_scaled_l.x(), 3.5);
    EXPECT_FLOAT_EQ(vec_scaled_l.y(), -7.0);
    EXPECT_FLOAT_EQ(vec_scaled_l.w(), 10.5);

    const gfx::Vector3 vec_scaled_r = scalar * vec;

    EXPECT_FLOAT_EQ(vec_scaled_r.x(), 3.5);
    EXPECT_FLOAT_EQ(vec_scaled_r.y(), -7.0);
    EXPECT_FLOAT_EQ(vec_scaled_r.w(), 10.5);
}

// Tests scalar multiplication using the shorthand multiplication operator
TEST(GraphicsVector3, ScalarMultplicationShorthand)
{
    gfx::Vector3 vec{ 1.0, -2.0, 3.0 };
    constexpr double scalar = 3.5;

    vec *= scalar;

    EXPECT_FLOAT_EQ(vec.x(), 3.5);
    EXPECT_FLOAT_EQ(vec.y(), -7.0);
    EXPECT_FLOAT_EQ(vec.w(), 10.5);
}

// Tests scalar multiplication by a fraction
TEST(GraphicsVector3, ScalarMultplicationFraction)
{
    const gfx::Vector3 vec{ 1.0, -2.0, 3.0 };
    constexpr double scalar = 0.5;

    const gfx::Vector3 vec_scaled = vec * scalar;

    EXPECT_FLOAT_EQ(vec_scaled.x(), 0.5);
    EXPECT_FLOAT_EQ(vec_scaled.y(), -1.0);
    EXPECT_FLOAT_EQ(vec_scaled.w(), 1.5);
}

// Tests scalar division using the division operator
TEST(GraphicsVector3, ScalarDivision)
{
    const gfx::Vector3 vec{ 1.0, -2.0, 3.0 };
    constexpr double scalar = 2.0;

    const gfx::Vector3 vec_scaled = vec / scalar;

    EXPECT_FLOAT_EQ(vec_scaled.x(), 0.5);
    EXPECT_FLOAT_EQ(vec_scaled.y(), -1.0);
    EXPECT_FLOAT_EQ(vec_scaled.w(), 1.5);
}

// Tests scalar division using the shorthand division operator
TEST(GraphicsVector3, ScalarDivisionShorthand)
{
    gfx::Vector3 vec{ 1.0, -2.0, 3.0 };
    constexpr double scalar = 2.0;

    vec /= scalar;

    EXPECT_FLOAT_EQ(vec.x(), 0.5);
    EXPECT_FLOAT_EQ(vec.y(), -1.0);
    EXPECT_FLOAT_EQ(vec.w(), 1.5);
}

// Tests matrix-vector multiplication using the multiplication operator
TEST(GraphicsVector3, MatrixMultiplicationOperator)
{
    const gfx::Matrix3 matrix{
            1.0, 2.0, 3.0,
            2.0, 4.0, 4.0,
            8.0, 6.0, 4.0
    };
    const gfx::Vector3 vector_a{ 1.0, 2.0, 3.0 };
    const gfx::Vector3 vector_expected{ 14, 22, 32 };

    const gfx::Vector3 vector_b = matrix * vector_a;

    EXPECT_TRUE(vector_b == vector_expected);
}

// Tests matrix-vector multiplication using the multiplication shorthand operator
TEST(GraphicsVector3, MatrixMultiplicationShorthandOperator)
{
    const gfx::Matrix3 matrix{
            1.0, 2.0, 3.0,
            2.0, 4.0, 4.0,
            8.0, 6.0, 4.0
    };
    const gfx::Vector3 vector_expected{ 14, 22, 32 };
    gfx::Vector3 vector_actual{ 1.0, 2.0, 3.0 };

    vector_actual *= matrix;

    EXPECT_TRUE(vector_actual == vector_expected);
}

// Tests the magnitude member function
TEST(GraphicsVector3, Magnitude)
{
    const gfx::Vector3 vec_a{ 0.0, 1.0, 0.0 };
    const gfx::Vector3 vec_b{ 0.0, 0.0, 1.0 };
    const gfx::Vector3 vec_c{ 1.0, 2.0, 3.0 };
    const gfx::Vector3 vec_d{ -1.0, -2.0, -3.0 };

    EXPECT_FLOAT_EQ(vec_a.magnitude(), 1.0);
    EXPECT_FLOAT_EQ(vec_b.magnitude(), 1.0);
    EXPECT_FLOAT_EQ(vec_c.magnitude(), std::sqrt(14));
    EXPECT_FLOAT_EQ(vec_d.magnitude(), std::sqrt(14));
}

// Tests the dot product function for vectors, and shows commutativity
TEST(GraphicsVector3, DotProduct)
{
    const gfx::Vector3 vec_a{ 1.0, 2.0, 3.0 };
    const gfx::Vector3 vec_b{ 2.0, 3.0, 4.0 };

    const double dot_l = dotProduct(vec_a, vec_b);
    const double dot_r = dotProduct(vec_b, vec_a);

    EXPECT_FLOAT_EQ(dot_l, 20.0);
    EXPECT_FLOAT_EQ(dot_r, 20.0);
}

// Tests the formatter specialization
TEST(GraphicsVector3, FormatterSpecialization)
{
    const gfx::Vector3 vec{ 1.515, 2.31607, 3.2 };
    const std::string str_expected{ "(1.515, 2.31607, 3.2)"};

    const std::string str_actual{ std::format("{}", vec) };

    EXPECT_TRUE(str_actual == str_expected);
}