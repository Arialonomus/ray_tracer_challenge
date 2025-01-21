#include "gtest/gtest.h"

#include "canvas.hpp"
#include "color.hpp"

#include <print>

// Tests the standard constructor
TEST(GraphicsCanvas, Constructor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Canvas canvas{ width, height };

    ASSERT_EQ(canvas.width(), width);
    ASSERT_EQ(canvas.height(), height);

    const gfx::Color black{ 0.0,0.0,0.0 };

    for (int col = 0; col < width; ++col)
        for (int row = 0; row < height; ++row) {
            gfx::Color pixel = canvas[col, row];
            ASSERT_TRUE(pixel == black);
        }
}

// Tests writing a pixel at a given coordinate
TEST(GraphicsCanvas, WritePixelColor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Canvas canvas{ width, height };
    const gfx::Color red{ 1.0,0.0,0.0 };

    canvas[2, 3] = red;
    const gfx::Color test_pixel = canvas[2, 3];
    ASSERT_TRUE(test_pixel == red);
}