#include "gtest/gtest.h"
#include "pattern.hpp"

#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

// Tests the default constructor for the base pattern class
TEST(GraphicsPattern, BaseClassDefaultConstructor)
{
    const gfx::TestPattern pattern{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    ASSERT_EQ(pattern.getTransform(), transform_expected);
}

// Tests the standard constructor for the base pattern class
TEST(GraphicsPattern, BaseClassStandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::TestPattern pattern{ transform_expected };

    ASSERT_EQ(pattern.getTransform(), transform_expected);
}

// Tests the copy constructor for the base pattern class
TEST(GraphicsPattern, BaseClassCopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::TestPattern pattern_src{ transform_expected };
    const gfx::TestPattern pattern_cpy{ pattern_src };

    ASSERT_EQ(pattern_cpy.getTransform(), transform_expected);
}

// Tests setting the transform for a base pattern class
TEST(GraphicsPattern, SetTransform)
{
    gfx::TestPattern pattern{ };
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };

    pattern.setTransform(transform_expected);

    ASSERT_EQ(pattern.getTransform(), transform_expected);
}