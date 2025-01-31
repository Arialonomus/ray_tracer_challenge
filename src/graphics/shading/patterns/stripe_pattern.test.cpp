#include "gtest/gtest.h"
#include "stripe_pattern.hpp"

#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

// Tests the color constructor for the stripe pattern class
TEST(GraphicsPatternStripe, ColorConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern stripe_pattern{ color_a_expected,
                                             color_b_expected };

    ASSERT_EQ(stripe_pattern.getTransform(), transform_expected);
    ASSERT_EQ(stripe_pattern.getColorA(), color_a_expected);
    ASSERT_EQ(stripe_pattern.getColorB(), color_b_expected);
}

// Tests the standard constructor for the stripe pattern class
TEST(GraphicsPatternStripe, StandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern stripe_pattern{ transform_expected,
                                             color_a_expected,
                                             color_b_expected };

    ASSERT_EQ(stripe_pattern.getTransform(), transform_expected);
    ASSERT_EQ(stripe_pattern.getColorA(), color_a_expected);
    ASSERT_EQ(stripe_pattern.getColorB(), color_b_expected);
}

// Tests the copy constructor for the stripe pattern class
TEST(GraphicsPatternStripe, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern stripe_pattern_src{ transform_expected,
                                                 color_a_expected,
                                                 color_b_expected };
    const gfx::StripePattern stripe_pattern_cpy{ stripe_pattern_src };

    ASSERT_EQ(stripe_pattern_cpy.getTransform(), transform_expected);
    ASSERT_EQ(stripe_pattern_cpy.getColorA(), color_a_expected);
    ASSERT_EQ(stripe_pattern_cpy.getColorB(), color_b_expected);
}

// Tests the assignment operator for the stripe pattern class
TEST(GraphicsPatternStripe, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern stripe_pattern_a{ transform_expected,
                                               color_a_expected,
                                               color_b_expected };
    gfx::StripePattern stripe_pattern_b{ gfx::createIdentityMatrix(),
                                         gfx::red(),
                                         gfx::blue() };

    stripe_pattern_b = stripe_pattern_a;

    ASSERT_EQ(stripe_pattern_b.getTransform(), transform_expected);
    ASSERT_EQ(stripe_pattern_b.getColorA(), color_a_expected);
    ASSERT_EQ(stripe_pattern_b.getColorB(), color_b_expected);
}

// Tests the equality operator for stripe pattern
TEST(GraphicsPatternStripe, EqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern stripe_pattern_src{ transform_expected,
                                                 color_a_expected,
                                                 color_b_expected };
    const gfx::StripePattern stripe_pattern_cpy{ stripe_pattern_src };

    ASSERT_TRUE(stripe_pattern_src == stripe_pattern_cpy);
}

// Tests that the default stripe pattern returns the correct color in each dimension
TEST(GraphicsPatternStripe, SampleColorAt)
{
    const gfx::StripePattern stripe_pattern{ gfx::white(), gfx::black() };

    // Test that a stripe pattern is constant in the y-dimension
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 1, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 2, 0)), gfx::white());

    // Test that a stripe pattern is constant in the z-dimension
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 0, 1)), gfx::white());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 0, 2)), gfx::white());

    // Test that a stripe pattern alternates in the y-dimension
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(0.9, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(1, 0, 0)), gfx::black());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(-0.1, 0, 0)), gfx::black());
    EXPECT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(-1, 0, 0)), gfx::black());
    ASSERT_EQ(stripe_pattern.samplePatternAt(gfx::createPoint(-1.1, 0, 0)), gfx::white());
}