#pragma once

#include <vector>
#include <mdspan>
#include <string>

#include "color.hpp"

namespace rt
{
    constexpr std::string_view PPM_IDENTIFIER{ "P3" };
    constexpr int PPM_MAX_COLOR_VALUE{ 255 };
    constexpr int PPM_MAX_LINE_LEN{ 70 };

    class Canvas
    {
    public:
        /* Constructors */

        Canvas() = delete;
        Canvas(const size_t width, const size_t height)
                : m_pixels{ width * height },
                  m_grid{ m_pixels.data(), width, height }
        {}
        Canvas(const size_t width, const size_t height, const gfx::Color& color)
                : m_pixels{ width * height, color },
                  m_grid{ m_pixels.data(), width, height }
        {}
        Canvas(const Canvas& src)
                : m_pixels{ src.m_pixels },
                  m_grid{ m_pixels.data(), src.width(), src.height() }
        {}
        Canvas(Canvas&& src) noexcept
                : m_pixels{ std::move(src.m_pixels) },
                  m_grid{ m_pixels.data(), src.width(), src.height() }
        {
            src.m_grid = { };
        }

        /* Destructor */

        ~Canvas() = default;

        /* Assignment Operators */

        Canvas& operator=(const Canvas&) = delete;
        Canvas& operator=(Canvas&&) = delete;

        /* Accessors */

        // Returns the width of the canvas, in pixels
        [[nodiscard]] size_t width() const
        { return m_grid.extents().extent(0); }

        // Returns the height of the canvas, in pixels
        [[nodiscard]] size_t height() const
        { return m_grid.extents().extent(1); }

        // Returns a reference to the color of the pixel at a given coordinate, in column-major order
        [[nodiscard]] gfx::Color& operator[](const size_t col, const size_t row) const
        { return m_grid[col, row]; }

    private:
        std::vector<gfx::Color> m_pixels;
        std::mdspan<
            gfx::Color,
            std::extents<size_t, std::dynamic_extent, std::dynamic_extent>,
            std::layout_left
        > m_grid;
    };

    /* Canvas Export Methods */

    // Returns a string containing the canvas color data in PPM format
    std::string exportAsPPM(const Canvas& canvas);
}