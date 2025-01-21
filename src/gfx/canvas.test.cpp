#include "gtest/gtest.h"

#include "canvas.hpp"

// Tests the standard constructor
TEST(GraphicsCanvas, Constructor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Canvas canvas{ width, height };

    ASSERT_EQ(canvas.width(), width);
    ASSERT_EQ(canvas.height(), height);
}