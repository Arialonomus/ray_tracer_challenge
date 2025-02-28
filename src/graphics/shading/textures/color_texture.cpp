#include "color_texture.hpp"

namespace gfx {
    bool ColorTexture::areEquivalent(const Texture& other_texture) const
    {
        const ColorTexture& other_color_texture{ dynamic_cast<const ColorTexture&>(other_texture) };
        return m_color == other_color_texture.m_color;
    }
}