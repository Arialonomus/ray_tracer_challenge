#include "gtest/gtest.h"
#include "gradient_pattern.hpp"

#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

// Tests the color constructor for the gradient pattern class
TEST(GraphicsPatternGradient, ColorConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::GradientPattern gradient_pattern{ color_a_expected,
                                             color_b_expected };

    ASSERT_EQ(gradient_pattern.getTransform(), transform_expected);
    ASSERT_EQ(gradient_pattern.getColorA(), color_a_expected);
    ASSERT_EQ(gradient_pattern.getColorB(), color_b_expected);
}

// Tests the standard constructor for the gradient pattern class
TEST(GraphicsPatternGradient, StandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::GradientPattern gradient_pattern{ transform_expected,
                                             color_a_expected,
                                             color_b_expected };

    ASSERT_EQ(gradient_pattern.getTransform(), transform_expected);
    ASSERT_EQ(gradient_pattern.getColorA(), color_a_expected);
    ASSERT_EQ(gradient_pattern.getColorB(), color_b_expected);
}

// Tests the copy constructor for the gradient pattern class
TEST(GraphicsPatternGradient, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::GradientPattern gradient_pattern_src{ transform_expected,
                                                 color_a_expected,
                                                 color_b_expected };
    const gfx::GradientPattern gradient_pattern_cpy{ gradient_pattern_src };

    ASSERT_EQ(gradient_pattern_cpy.getTransform(), transform_expected);
    ASSERT_EQ(gradient_pattern_cpy.getColorA(), color_a_expected);
    ASSERT_EQ(gradient_pattern_cpy.getColorB(), color_b_expected);
}

// Tests the assignment operator for the gradient pattern class
TEST(GraphicsPatternGradient, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::GradientPattern gradient_pattern_a{ transform_expected,
                                               color_a_expected,
                                               color_b_expected };
    gfx::GradientPattern gradient_pattern_b{ gfx::createIdentityMatrix(),
                                         gfx::red(),
                                         gfx::blue() };

    gradient_pattern_b = gradient_pattern_a;

    ASSERT_EQ(gradient_pattern_b.getTransform(), transform_expected);
    ASSERT_EQ(gradient_pattern_b.getColorA(), color_a_expected);
    ASSERT_EQ(gradient_pattern_b.getColorB(), color_b_expected);
}

// Tests the equality operator for gradient pattern
TEST(GraphicsPatternGradient, EqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::GradientPattern gradient_pattern_src{ transform_expected,
                                                 color_a_expected,
                                                 color_b_expected };
    const gfx::GradientPattern gradient_pattern_cpy{ gradient_pattern_src };

    ASSERT_TRUE(gradient_pattern_src == gradient_pattern_cpy);
}

// Tests that the default gradient pattern returns the correct color in each dimension
TEST(GraphicsPatternGradient, SampleColorAt)
{
    const gfx::GradientPattern gradient_pattern{ gfx::white(), gfx::black() };

    // Test sampling the left edge
    const gfx::Color color_a_expected{ gfx::white() };
    const gfx::Color color_a_actual{ gradient_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)) };
    EXPECT_EQ(color_a_actual, color_a_expected);

    // Test sampling 25% from the left edge
    const gfx::Color color_b_expected{ 0.75, 0.75, 0.75 };
    const gfx::Color color_b_actual{ gradient_pattern.samplePatternAt(gfx::createPoint(0.25, 0, 0)) };
    EXPECT_EQ(color_b_actual, color_b_expected);

    // Test sampling 50% from the left edge
    const gfx::Color color_c_expected{ 0.5, 0.5, 0.5 };
    const gfx::Color color_c_actual{ gradient_pattern.samplePatternAt(gfx::createPoint(0.5, 0, 0)) };
    EXPECT_EQ(color_c_actual, color_c_expected);

    // Test sampling 75% from the left edge
    const gfx::Color color_d_expected{ 0.25, 0.25, 0.25 };
    const gfx::Color color_d_actual{ gradient_pattern.samplePatternAt(gfx::createPoint(0.75, 0, 0)) };
    EXPECT_EQ(color_d_actual, color_d_expected);
}

