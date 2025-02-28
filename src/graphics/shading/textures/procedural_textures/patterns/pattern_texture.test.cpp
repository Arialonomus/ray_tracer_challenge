#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "pattern_texture_3d.hpp"

#include "transform.hpp"
#include "color.hpp"

#include "stripe_pattern_3d.hpp"
#include "ring_pattern_3d.hpp"
#include "checkered_pattern_3d.hpp"

// Tests the texture-only constructor for the abstract pattern class
TEST(GraphicsPatternTexture, TextureOnlyConstructor)
{
    const gfx::Matrix4 transform_expected{ };
    const gfx::StripePattern3D texture_a_expected{ gfx::createYRotationMatrix(M_PI_4),
                                                   gfx::white(),
                                                   gfx::black() };
    const gfx::StripePattern3D texture_b_expected{ gfx::createYRotationMatrix(M_PI_4),
                                                   gfx::cyan(),
                                                   gfx::magenta() };
    const TestPattern3D test_pattern{ texture_a_expected,
                                      texture_b_expected };

    ASSERT_EQ(test_pattern.getTransform(), transform_expected);
    ASSERT_EQ(test_pattern.getTextureA(), texture_a_expected);
    ASSERT_EQ(test_pattern.getTextureB(), texture_b_expected);
}

// Tests the color-only constructor for the abstract pattern class
TEST(GraphicsPatternTexture, ColorOnlyConstructor)
{
    const gfx::Matrix4 transform_expected{ };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestPattern3D test_pattern{ color_a_expected, color_b_expected };
    const gfx::TextureMap map{ gfx::ProjectionMap };

    ASSERT_EQ(test_pattern.getTransform(), transform_expected);
    
    const gfx::Vector4 test_point{ gfx::createPoint(0, 0, 0) };
    ASSERT_EQ(test_pattern.getTextureA().getTextureColorAt(test_point, map), color_a_expected);
    ASSERT_EQ(test_pattern.getTextureB().getTextureColorAt(test_point, map), color_b_expected);
}

// Tests the standard constructors for the two-tone pattern class
TEST(GraphicsPatternTexture, StandardConstructors)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::StripePattern3D texture_a_expected{ gfx::createYRotationMatrix(M_PI_4),
                                                   gfx::white(),
                                                   gfx::black() };
    const gfx::StripePattern3D texture_b_expected{ gfx::createYRotationMatrix(M_PI_4),
                                                   gfx::cyan(),
                                                   gfx::magenta() };
    const gfx::TextureMap map{ gfx::ProjectionMap };

    // Test the texture argument standard constructor
    const TestPattern3D test_pattern_textures{ transform_expected,
                                               texture_a_expected,
                                               texture_b_expected };

    ASSERT_EQ(test_pattern_textures.getTransform(), transform_expected);
    ASSERT_EQ(test_pattern_textures.getTextureA(), texture_a_expected);
    ASSERT_EQ(test_pattern_textures.getTextureB(), texture_b_expected);

    // Test the color argument standard constructor
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestPattern3D test_pattern_colors{ transform_expected,
                                             color_a_expected,
                                             color_b_expected };

    const gfx::Vector4 test_point{ gfx::createPoint(0, 0, 0) };
    ASSERT_EQ(test_pattern_colors.getTransform(), transform_expected);
    ASSERT_EQ(test_pattern_colors.getTextureA().getTextureColorAt(test_point, map), color_a_expected);
    ASSERT_EQ(test_pattern_colors.getTextureB().getTextureColorAt(test_point, map), color_b_expected);
}

// Tests the copy constructor for the two-tone pattern class
TEST(GraphicsPatternTexture, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const TestPattern3D test_pattern_src{ transform_expected,
                                          color_a_expected,
                                          color_b_expected };
    const TestPattern3D test_pattern_cpy{ test_pattern_src };

    ASSERT_EQ(test_pattern_cpy, test_pattern_src);
}

/* Stripe Pattern Derived Class Tests */

// Tests the equality operator for stripe patterns
TEST(GraphicsPatternTexture, StripePatternEqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::StripePattern3D stripe_pattern_src{ transform_expected,
                                                   color_a_expected,
                                                   color_b_expected };
    const gfx::StripePattern3D stripe_pattern_cpy{ stripe_pattern_src };

    ASSERT_TRUE(stripe_pattern_src == stripe_pattern_cpy);
}

// Tests that the default stripe pattern returns the correct color in each dimension
TEST(GraphicsPatternTexture, StripePatternGetTextureColorAt)
{
    const gfx::StripePattern3D stripe_pattern{ gfx::white(), gfx::black() };
    const gfx::TextureMap map{ gfx::ProjectionMap };

    // Test that a stripe pattern is constant in the y-dimension
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0),map), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 1, 0),map), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 2, 0), map), gfx::white());

    // Test that a stripe pattern is constant in the z-dimension
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0), map), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 0, 1), map), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 0, 2), map), gfx::white());

    // Test that a stripe pattern alternates in the y-dimension
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0), map), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(0.9, 0, 0), map), gfx::white());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(1, 0, 0), map), gfx::black());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(-0.1, 0, 0), map), gfx::black());
    EXPECT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(-1, 0, 0), map), gfx::black());
    ASSERT_EQ(stripe_pattern.getTextureColorAt(gfx::createPoint(-1.1, 0, 0), map), gfx::white());
}

/* Ring Pattern Derived Class Tests */

// Tests the equality operator for ring patterns
TEST(GraphicsPatternTexture, RingPatternEqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::StripePattern3D texture_a_expected{ gfx::createYRotationMatrix(M_PI_4),
                                                   gfx::white(),
                                                   gfx::black() };
    const gfx::StripePattern3D texture_b_expected{ gfx::createYRotationMatrix(M_PI_4),
                                                   gfx::cyan(),
                                                   gfx::magenta() };
    const gfx::RingPattern3D ring_pattern_src{ transform_expected,
                                               texture_a_expected,
                                               texture_b_expected };
    const gfx::RingPattern3D ring_pattern_cpy{ ring_pattern_src };

    ASSERT_TRUE(ring_pattern_src == ring_pattern_cpy);
}

// Tests that the default ring pattern returns the correct color when sampled
TEST(GraphicsPatternTexture, RingPatternGetTextureColorAt)
{
    const gfx::RingPattern3D ring_pattern{ gfx::white(), gfx::black() };
    const gfx::TextureMap map{ gfx::ProjectionMap };

    const gfx::Color color_a_actual{ ring_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0), map) };
    EXPECT_EQ(color_a_actual, gfx::white());

    const gfx::Color color_b_actual{ ring_pattern.getTextureColorAt(gfx::createPoint(1, 0, 0), map) };
    EXPECT_EQ(color_b_actual, gfx::black());

    const gfx::Color color_c_actual{ ring_pattern.getTextureColorAt(gfx::createPoint(0, 0, 1), map) };
    EXPECT_EQ(color_c_actual, gfx::black());

    const gfx::Color color_d_actual{ ring_pattern.getTextureColorAt(gfx::createPoint(0.708, 0, 0.708), map) };
    EXPECT_EQ(color_d_actual, gfx::black());
}

/* Checkered Pattern Derived Class Tests */

// Tests the equality operator for ring patterns
TEST(GraphicsPatternTexture, CheckeredPatternEqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2,3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::CheckeredPattern3D checkered_pattern_src{ transform_expected,
                                                         color_a_expected,
                                                         color_b_expected };
    const gfx::CheckeredPattern3D checkered_pattern_cpy{ checkered_pattern_src };

    ASSERT_TRUE(checkered_pattern_src == checkered_pattern_cpy);
}

// Tests that the checkered ring pattern repeats in each dimension
TEST(GraphicsPatternTexture, CheckeredPatternGetTextureColorAt)
{
    const gfx::CheckeredPattern3D checkered_pattern{ gfx::white(), gfx::black() };
    const gfx::TextureMap map{ gfx::ProjectionMap };

    // Test that checkers repeat in the x-dimension
    const gfx::Color color_x_a_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0), map) };
    EXPECT_EQ(color_x_a_actual, gfx::white());
    const gfx::Color color_x_b_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0.99, 0, 0), map) };
    EXPECT_EQ(color_x_b_actual, gfx::white());
    const gfx::Color color_x_c_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(1.01, 0, 0), map) };
    EXPECT_EQ(color_x_c_actual, gfx::black());

    // Test that checkers repeat in the y-dimension
    const gfx::Color color_y_a_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0), map) };
    EXPECT_EQ(color_y_a_actual, gfx::white());
    const gfx::Color color_y_b_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 0.99, 0), map) };
    EXPECT_EQ(color_y_b_actual, gfx::white());
    const gfx::Color color_y_c_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 1.01, 0), map) };
    EXPECT_EQ(color_y_c_actual, gfx::black());

    // Test that checkers repeat in the z-dimension
    const gfx::Color color_z_a_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0), map) };
    EXPECT_EQ(color_z_a_actual, gfx::white());
    const gfx::Color color_z_b_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 0, 0.99), map) };
    EXPECT_EQ(color_z_b_actual, gfx::white());
    const gfx::Color color_z_c_actual{ checkered_pattern.getTextureColorAt(gfx::createPoint(0, 0, 1.01), map) };
    EXPECT_EQ(color_z_c_actual, gfx::black());
}

#pragma clang diagnostic pop