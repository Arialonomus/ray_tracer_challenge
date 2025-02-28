#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"

#include "color_texture.hpp"

/* Color Texture Derived Class Tests */

// Tests the equality operator for color textures
TEST(GraphicsTexture, ColorTextureEqualityOperator)
{
    const gfx::Color color{ gfx::cyan() };
    const gfx::ColorTexture color_texture_a{ color };
    const gfx::ColorTexture color_texture_b{ color };

    ASSERT_TRUE(color_texture_a == color_texture_b);
}

// Tests that a color texture returns the correct color when sampled
TEST(GraphicsTexture, ColorTextureGetTextureColorAt)
{
    const gfx::Color color_expected{ gfx::cyan() };
    const gfx::ColorTexture color_texture{ color_expected };

    const gfx::Color color_texture_color_actual{
            color_texture.getTextureColorAt(gfx::createPoint(0.75, 1, 0),
                                            gfx::ProjectionMap)
    };
    EXPECT_EQ(color_texture_color_actual, color_expected);
}

#pragma clang diagnostic pop