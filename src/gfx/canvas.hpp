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
        Canvas(const size_t width, const size_t height) : m_pixels(width* height), m_grid(m_pixels.data(), height, width) {}

    private:
        std::vector<Color> m_pixels;
        std::mdspan<Color, std::extents<size_t, std::dynamic_extent, std::dynamic_extent>, std::layout_left> m_grid;
    };
}