#include "gtest/gtest.h"
#include "two_tone_pattern.hpp"
#include "stripe_pattern.hpp"
#include "gradient_pattern.hpp"
#include "ring_pattern.hpp"

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

// Tests setting the pattern colors
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