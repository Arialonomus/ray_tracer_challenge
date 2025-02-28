#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"

#include "color.hpp"
#include "transform.hpp"
#include "texture_map.hpp"

#include "color_texture.hpp"
#include "gradient_texture.hpp"

/* Gradient Texture Derived Class Tests */

// Tests the equality operator for gradient textures
TEST(GraphicsProceduralTexture, GradientTextureEqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(1, 2, 3) };
    const gfx::Color color_a_expected{ gfx::black() };
    const gfx::Color color_b_expected{ gfx::white() };
    const gfx::GradientTexture gradient_pattern_src{ transform_expected,
                                                     color_a_expected,
                                                     color_b_expected };
    const gfx::GradientTexture gradient_pattern_cpy{ gradient_pattern_src };

    ASSERT_TRUE(gradient_pattern_src == gradient_pattern_cpy);
}

// Tests that a gradient texture returns the correct color when sampled
TEST(GraphicsProceduralTexture, GradientTextureGetTextureColorAt)
{
    const gfx::GradientTexture gradient_texture{ gfx::white(), gfx::black() };

    // Test sampling the left edge
    const gfx::Color color_a_expected{ gfx::white() };
    const gfx::Color color_a_actual{
        gradient_texture.getTextureColorAt(gfx::createPoint(0, 0, 0),
                                           gfx::ProjectionMap) };
    EXPECT_EQ(color_a_actual, color_a_expected);

    // Test sampling 25% from the left edge
    const gfx::Color color_b_expected{ 0.75, 0.75, 0.75 };
    const gfx::Color color_b_actual{
            gradient_texture.getTextureColorAt(gfx::createPoint(0.25, 0, 0),
                                               gfx::ProjectionMap) };
    EXPECT_EQ(color_b_actual, color_b_expected);

    // Test sampling 50% from the left edge
    const gfx::Color color_c_expected{ 0.5, 0.5, 0.5 };
    const gfx::Color color_c_actual{
            gradient_texture.getTextureColorAt(gfx::createPoint(0.5, 0, 0),
                                               gfx::ProjectionMap) };
    EXPECT_EQ(color_c_actual, color_c_expected);

    // Test sampling 75% from the left edge
    const gfx::Color color_d_expected{ 0.25, 0.25, 0.25 };
    const gfx::Color color_d_actual{
            gradient_texture.getTextureColorAt(gfx::createPoint(0.75, 0, 0),
                                               gfx::ProjectionMap) };
    EXPECT_EQ(color_d_actual, color_d_expected);
}

#pragma clang diagnostic pop