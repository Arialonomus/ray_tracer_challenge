#include "gtest/gtest.h"
#include "pattern.hpp"
#include "stripe_pattern.hpp"

#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

/* Pattern Base Class */

class TestPattern : public gfx::Pattern
{
public:
    TestPattern()
            : Pattern{ }
    {}
    explicit TestPattern(const gfx::Matrix4& transform_matrix)
            : Pattern{ transform_matrix }
    {}

    [[nodiscard]] gfx::Color getSurfaceColorAt(const gfx::Vector4& point) const override
    { return gfx::Color{ }; }

    [[nodiscard]] std::unique_ptr<Pattern> clone() const override
    { return std::make_unique<TestPattern>(*this); }

private:
    [[nodiscard]] bool equal(const Pattern& other) const override
    { return this->getTransform() == other.getTransform(); }
};

// Tests the default constructor for the base pattern class
TEST(GraphicsPattern, BaseClassDefaultConstructor)
{
    const TestPattern pattern{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(pattern.getTransform(), transform_expected);
}

// Tests the standard constructor for the base pattern class
TEST(GraphicsPattern, BaseClassStandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const TestPattern pattern{ transform_expected };

    ASSERT_EQ(pattern.getTransform(), transform_expected);
}

// Tests the copy constructor for the base pattern class
TEST(GraphicsPattern, BaseClassCopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const TestPattern pattern_src{ transform_expected };
    const TestPattern pattern_cpy{ pattern_src };

    ASSERT_EQ(pattern_cpy.getTransform(), transform_expected);
}

// Tests setting the transform for a base pattern class
TEST(GraphicsPattern, SetTransform)
{
    TestPattern pattern{ };
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };

    pattern.setTransform(transform_expected);

    ASSERT_EQ(pattern.getTransform(), transform_expected);
}

/* StripePattern Derived Class */

// Tests the color constructor for the stripe pattern class
TEST(GraphicsPattern, StripePatternColorConstructor)
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
TEST(GraphicsPattern, StripePatternStandardConstructor)
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
TEST(GraphicsPattern, StripePatternCopyConstructor)
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
TEST(GraphicsPattern, StripePatternAssignmentOperator)
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
TEST(GraphicsPattern, StripePatternEqualityOperator)
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
TEST(GraphicsPattern, StripePatternGetColorAtNoTransform)
{
    const gfx::StripePattern stripe_pattern{ gfx::white(), gfx::black() };

    // Test that a stripe pattern is constant in the y-dimension
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 1, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 2, 0)), gfx::white());

    // Test that a stripe pattern is constant in the z-dimension
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 0, 1)), gfx::white());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 0, 2)), gfx::white());

    // Test that a stripe pattern alternates in the y-dimension
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(0.9, 0, 0)), gfx::white());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(1, 0, 0)), gfx::black());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(-0.1, 0, 0)), gfx::black());
    EXPECT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(-1, 0, 0)), gfx::black());
    ASSERT_EQ(stripe_pattern.getSurfaceColorAt(gfx::createPoint(-1.1, 0, 0)), gfx::white());
}