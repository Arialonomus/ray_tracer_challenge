#include "gtest/gtest.h"
#include "pattern.hpp"

#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

class TestPattern : public gfx::Pattern
{
public:
    TestPattern()
            : Pattern{ }
    {}
    explicit TestPattern(const gfx::Matrix4& transform_matrix)
            : Pattern{ transform_matrix }
    {}

    [[nodiscard]] gfx::Color samplePatternAt(const gfx::Vector4& point) const override
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