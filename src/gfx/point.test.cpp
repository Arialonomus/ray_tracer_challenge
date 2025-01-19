
#include <pch.h>
#include "point.hpp"
#include "vector.hpp"

// Tests the default constructor
TEST(GraphicsPoint, DefaultConstructor)
{
    const gfx::Point pt;

    ASSERT_FLOAT_EQ(pt.x(), 0.0);
    ASSERT_FLOAT_EQ(pt.y(), 0.0);
    ASSERT_FLOAT_EQ(pt.z(), 0.0);
    ASSERT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the standard constructor
TEST(GraphicsPoint, Constructor)
{
    const gfx::Point pt{ 4.0, -4.0, 3.0 };

    ASSERT_FLOAT_EQ(pt.x(), 4.0);
    ASSERT_FLOAT_EQ(pt.y(), -4.0);
    ASSERT_FLOAT_EQ(pt.z(), 3.0);
    ASSERT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the homogeneous coordinate constructor
TEST(GraphicsPoint, HomogeneousConstructor)
{
    const gfx::Point pt{ 4.0, -4.0, 3.0, 0.5 };

    ASSERT_FLOAT_EQ(pt.x(), 4.0);
    ASSERT_FLOAT_EQ(pt.y(), -4.0);
    ASSERT_FLOAT_EQ(pt.z(), 3.0);
    ASSERT_FLOAT_EQ(pt.w(), 0.5);
}


// Tests the copy constructor
TEST(GraphicsPoint, CopyConstructor)
{
    const gfx::Point pt_src{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_cpy{ pt_src };

    ASSERT_FLOAT_EQ(pt_cpy.x(), 4.0);
    ASSERT_FLOAT_EQ(pt_cpy.y(), -4.0);
    ASSERT_FLOAT_EQ(pt_cpy.z(), 3.0);
    ASSERT_FLOAT_EQ(pt_cpy.w(), 1.0);
}

// Tests the assignment operator
TEST(GraphicsPoint, AssignmentOperator)
{
    gfx::Point pt_a{ 1.0, 2.0, 3.0 };
    const gfx::Point pt_b{ 17.0, -3.5, 1.2 };

    pt_a = pt_b;

    ASSERT_FLOAT_EQ(pt_a.x(), 17.0);
    ASSERT_FLOAT_EQ(pt_a.y(), -3.5);
    ASSERT_FLOAT_EQ(pt_a.z(), 1.2);
    ASSERT_FLOAT_EQ(pt_a.w(), 1.0);
}

// Tests the equality operator
TEST(GraphicsPoint, EqualityOperator)
{
    const gfx::Point pt_a{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_b{ 4.0, -4.0, 3.0 };

    EXPECT_TRUE(pt_a == pt_b);
}

// Tests the inequality operator
TEST(GraphicsPoint, InequalityOperator)
{
    const gfx::Point pt_a{ 4.0, -4.0, 3.0 };
    const gfx::Point pt_b{ 0.0, 5.0, -2.0 };

    EXPECT_TRUE(pt_a != pt_b);
}

// Tests the point translation (point-vector addition) operator and show commutativity
TEST(GraphicsPoint, PointTranslation)
{
    const gfx::Point pt{ 3.0, -2.0, 5.0, 1.0 };
    const gfx::Vector vec{ -2.0, 3.0, 1.0, 0.0 };

    const gfx::Point pt_translated_l = pt + vec;

    EXPECT_FLOAT_EQ(pt_translated_l.x(), 1.0);
    EXPECT_FLOAT_EQ(pt_translated_l.y(), 1.0);
    EXPECT_FLOAT_EQ(pt_translated_l.z(), 6.0);
    EXPECT_FLOAT_EQ(pt_translated_l.w(), 1.0);

    const gfx::Point pt_translated_r = vec + pt;

    EXPECT_FLOAT_EQ(pt_translated_r.x(), 1.0);
    EXPECT_FLOAT_EQ(pt_translated_r.y(), 1.0);
    EXPECT_FLOAT_EQ(pt_translated_r.z(), 6.0);
    EXPECT_FLOAT_EQ(pt_translated_r.w(), 1.0);
}

// Tests the point translation (point-vector addition) shorthand operator
TEST(GraphicsPoint, PointTranslationShorthandOperator)
{
    gfx::Point pt{ 3.0, -2.0, 5.0, 1.0 };
    const gfx::Vector vec{ -2.0, 3.0, 1.0, 0.0 };

    pt += vec;

    EXPECT_FLOAT_EQ(pt.x(), 1.0);
    EXPECT_FLOAT_EQ(pt.y(), 1.0);
    EXPECT_FLOAT_EQ(pt.z(), 6.0);
    EXPECT_FLOAT_EQ(pt.w(), 1.0);
}

// Tests the point reverse translation (point-vector subtraction) operator
TEST(GraphicsPoint, PointReverseTranslation)
{
    const gfx::Point pt{ 3.0, 2.0, 1.0 };
    const gfx::Vector vec{ 5.0, 6.0, 7.0 };

    const gfx::Point pt_translated_l = pt - vec;

    EXPECT_FLOAT_EQ(pt_translated_l.x(), -2.0);
    EXPECT_FLOAT_EQ(pt_translated_l.y(), -4.0);
    EXPECT_FLOAT_EQ(pt_translated_l.z(), -6.0);
    EXPECT_FLOAT_EQ(pt_translated_l.w(), 1.0);

}

// Tests the point reverse translation (point-vector subtraction) shorthand operator
TEST(GraphicsPoint, PointReverseTranslationShorthandOperator)
{
    gfx::Point pt{ 3.0, 2.0, 1.0 };
    const gfx::Vector vec{ 5.0, 6.0, 7.0 };

    pt -= vec;

    EXPECT_FLOAT_EQ(pt.x(), -2.0);
    EXPECT_FLOAT_EQ(pt.y(), -4.0);
    EXPECT_FLOAT_EQ(pt.z(), -6.0);
    EXPECT_FLOAT_EQ(pt.w(), 1.0);
}


// Tests the distance vector (point-point subtraction) operator
TEST(GraphicsPoint, DistanceVector)
{
    const gfx::Point pt_a{ 3.0, 2.0, 1.0 };
    const gfx::Point pt_b{ 5.0, 6.0, 7.0 };

    const gfx::Vector distance = pt_a - pt_b;

    EXPECT_FLOAT_EQ(distance.x(), -2.0);
    EXPECT_FLOAT_EQ(distance.y(), -4.0);
    EXPECT_FLOAT_EQ(distance.z(), -6.0);
    EXPECT_FLOAT_EQ(distance.w(), 0.0);
}
