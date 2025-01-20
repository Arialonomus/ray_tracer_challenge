#include <pch.h>
#include "canvas.hpp"

#include "color.hpp"

// Tests the standard constructor
TEST(GraphicsCanvas, Constructor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Canvas canvas{ width, height };

    ASSERT_EQ(canvas.width(), width);
    ASSERT_EQ(canvas.height(), height);

    const gfx::Color black{ 0.0, 0.0, 0.0 };

    for (int i : width)
    {
        for (int j : height)
        {
            ASSERT_EQ(canvas[i, j], black);
        }
    }
}