#pragma once

#include <vector>
#include <mdspan>

#include "color.hpp"

namespace gfx
{
    class Canvas
    {
    public:
        /* Constructors */

        Canvas() = delete;
        Canvas(const size_t width, const size_t height)
                : m_pixels(width * height),
                  m_grid(m_pixels.data(), width, height)
        {}

        /* Accessors */

        // Returns the width of the canvas, in pixels
        [[nodiscard]] size_t width() const
        { return m_grid.extents().extent(0); }

        // Returns the height of the canvas, in pixels
        [[nodiscard]] size_t height() const
        { return m_grid.extents().extent(1); }

        // Returns a reference the color of the pixel at a given coordinate, in column-major order
        [[nodiscard]] Color& operator[](const size_t col, const size_t row) const
        { return m_grid[col, row]; }

    private:
        std::vector<Color> m_pixels;
        std::mdspan<Color, std::extents<size_t, std::dynamic_extent, std::dynamic_extent>, std::layout_left> m_grid;
    };
}