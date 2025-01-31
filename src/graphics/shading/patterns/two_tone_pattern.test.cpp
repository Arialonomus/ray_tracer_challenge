#include "gtest/gtest.h"
#include "two_tone_pattern.hpp"
#include "stripe_pattern.hpp"
#include "gradient_pattern.hpp"
#include "ring_pattern.hpp"
#include "checkered_pattern.hpp"

#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

class TestTwoTonePattern : public gfx::TwoTonePattern
{
public:
    TestTwoTonePattern() = delete;
    TestTwoTonePattern(const gfx::Color& color_a, const gfx::Color& color_b)
            : TwoTonePattern{ color_a, color_b }
    {}
    TestTwoTonePattern(const gfx::Matrix4& transform_matrix, const gfx::Color& color_a, const gfx::Color& color_b)
            : TwoTonePattern{ transform_matrix, color_a, color_b }
    {}

    [[nodiscard]] gfx::Color samplePatternAt(const gfx::Vector4& point) const override
    { return gfx::Color{ }; }

    [[nodiscard]] std::unique_ptr<Pattern> clone() const override
    { return std::make_unique<TestTwoTonePattern>(*this); }

private:
    [[nodiscard]] bool equal(const Pattern& other) const override
    {
        const TestTwoTonePattern& other_two_tone_pattern{ dynamic_cast<const TestTwoTonePattern&>(other) };
        return this->getTransform() == other_two_tone_pattern.getTransform() &&
             this->getColorA() == other_two_tone_pattern.getColorA() &&
             this->getColorB() == other_two_tone_pattern.getColorB(); 
    }
};

// Tests the color-only constructor for the two-tone pattern class
TEST(GraphicsPatternTwoTone, ColorOnlyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestTwoTonePattern two_tone_pattern{ color_a_expected, color_b_expected };

    ASSERT_EQ(two_tone_pattern.getTransform(), transform_expected);
    ASSERT_EQ(two_tone_pattern.getColorA(), color_a_expected);
    ASSERT_EQ(two_tone_pattern.getColorB(), color_b_expected);
}


// Tests the standard constructor for the two-tone pattern class
TEST(GraphicsPatternTwoTone, StandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestTwoTonePattern two_tone_pattern{ transform_expected,
                                               color_a_expected,
                                               color_b_expected };

    ASSERT_EQ(two_tone_pattern.getTransform(), transform_expected);
    ASSERT_EQ(two_tone_pattern.getColorA(), color_a_expected);
    ASSERT_EQ(two_tone_pattern.getColorB(), color_b_expected);
}

// Tests the copy constructor for the two-tone pattern class
TEST(GraphicsPatternTwoTone, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestTwoTonePattern two_tone_pattern_src{ transform_expected,
                                                   color_a_expected,
                                                   color_b_expected };
    const TestTwoTonePattern two_tone_pattern_cpy{ two_tone_pattern_src };

    ASSERT_EQ(two_tone_pattern_cpy.getTransform(), transform_expected);
}

// Tests setting the two-tone pattern colors
TEST(GraphicsPatternTwoTone, Mutators)
{
    TestTwoTonePattern two_tone_pattern{ gfx::black(), gfx::white() };

    // setColorA (Color Object)
    const gfx::Color color_a_expected{ 0.5, 0.5, 0.5 };
    two_tone_pattern.setColorA(color_a_expected);
    ASSERT_EQ(two_tone_pattern.getColorA(), color_a_expected);

    // setColorA (Float List)
    two_tone_pattern.setColorA(1, 1, 1);
    ASSERT_EQ(two_tone_pattern.getColorA(), gfx::white());

    // setColorB (Color Object)
    const gfx::Color color_b_expected{ 0.5, 0.5, 0.5 };
    two_tone_pattern.setColorB(color_b_expected);
    ASSERT_EQ(two_tone_pattern.getColorB(), color_b_expected);

    // setColorB (Float List)
    two_tone_pattern.setColorB(0, 0, 0);
    ASSERT_EQ(two_tone_pattern.getColorB(), gfx::black());
}

/* Stripe Derived Class Tests */

// Tests the equality operator for stripe patterns
TEST(GraphicsPatternTwoTone, StripePatternEqualityOperator)
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
TEST(GraphicsPatternTwoTone, StripePatternSampleColorAt)
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

/* Gradient Pattern Derived Class Tests */

// Tests the equality operator for gradient patterns
TEST(GraphicsPatternTwoTone, GradientPatternEqualityOperator)
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

// Tests that the default gradient pattern returns the correct color when sampled
TEST(GraphicsPatternTwoTone, GradientPatternSampleColorAt)
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

/* Ring Pattern Derived Class Tests */

// Tests the equality operator for ring patterns
TEST(GraphicsPatternTwoTone, RingPatternEqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::RingPattern ring_pattern_src{ transform_expected,
                                                 color_a_expected,
                                                 color_b_expected };
    const gfx::RingPattern ring_pattern_cpy{ ring_pattern_src };

    ASSERT_TRUE(ring_pattern_src == ring_pattern_cpy);
}

// Tests that the default ring pattern returns the correct color when sampled
TEST(GraphicsPatternTwoTone, RingPatternSampleColorAt)
{
    const gfx::RingPattern ring_pattern{ gfx::white(), gfx::black() };

    const gfx::Color color_a_actual{ ring_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)) };
    EXPECT_EQ(color_a_actual, gfx::white());

    const gfx::Color color_b_actual{ ring_pattern.samplePatternAt(gfx::createPoint(1, 0, 0)) };
    EXPECT_EQ(color_b_actual, gfx::black());

    const gfx::Color color_c_actual{ ring_pattern.samplePatternAt(gfx::createPoint(0, 0, 1)) };
    EXPECT_EQ(color_c_actual, gfx::black());

    const gfx::Color color_d_actual{ ring_pattern.samplePatternAt(gfx::createPoint(0.708, 0, 0.708)) };
    EXPECT_EQ(color_d_actual, gfx::black());
}

/* Checkered Pattern Derived Class Tests */

// Tests the equality operator for ring patterns
TEST(GraphicsPatternTwoTone, CheckeredPatternEqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::CheckeredPattern checkered_pattern_src{ transform_expected,
                                                      color_a_expected,
                                                      color_b_expected };
    const gfx::CheckeredPattern checkered_pattern_cpy{ checkered_pattern_src };

    ASSERT_TRUE(checkered_pattern_src == checkered_pattern_cpy);
}

// Tests that the checkered ring pattern repeats in each dimension
TEST(GraphicsPatternTwoTone, CheckeredPatternSampleColorAt)
{
    const gfx::CheckeredPattern checkered_pattern{ gfx::white(), gfx::black() };

    // Test that checkers repeat in the x-dimension
    const gfx::Color color_x_a_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)) };
    EXPECT_EQ(color_x_a_actual, gfx::white());
    const gfx::Color color_x_b_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0.99, 0, 0)) };
    EXPECT_EQ(color_x_b_actual, gfx::white());
    const gfx::Color color_x_c_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(1.01, 0, 0)) };
    EXPECT_EQ(color_x_c_actual, gfx::black());

    // Test that checkers repeat in the y-dimension
    const gfx::Color color_y_a_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)) };
    EXPECT_EQ(color_y_a_actual, gfx::white());
    const gfx::Color color_y_b_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 0.99, 0)) };
    EXPECT_EQ(color_y_b_actual, gfx::white());
    const gfx::Color color_y_c_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 1.01, 0)) };
    EXPECT_EQ(color_y_c_actual, gfx::black());

    // Test that checkers repeat in the z-dimension
    const gfx::Color color_z_a_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 0, 0)) };
    EXPECT_EQ(color_z_a_actual, gfx::white());
    const gfx::Color color_z_b_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 0, 0.99)) };
    EXPECT_EQ(color_z_b_actual, gfx::white());
    const gfx::Color color_z_c_actual{ checkered_pattern.samplePatternAt(gfx::createPoint(0, 0, 1.01)) };
    EXPECT_EQ(color_z_c_actual, gfx::black());
}