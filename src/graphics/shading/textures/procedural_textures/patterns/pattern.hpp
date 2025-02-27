#pragma once

#include "texture.hpp"
#include "color_texture.hpp"

namespace gfx {
    class Pattern : public Texture
    {
    public:
        /* Constructors */

        // Default Constructor
        Pattern() = delete;

        // Texture-Only Constructor
        Pattern(const Texture& texture_a, const Texture& texture_b)
                : Texture{ },
                  m_texture_a{ texture_a.clone() },
                  m_texture_b{ texture_b.clone() }
        {}

        // Color-Only Constructor
        Pattern(const Color& color_a, const Color& color_b)
                : Texture{ },
                  m_texture_a{ ColorTexture{ color_a }.clone() },
                  m_texture_b{ ColorTexture{ color_b }.clone() }
        {}

        // Standard Constructor (Textures)
        Pattern(const Matrix3& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : Texture{ transform_matrix },
                  m_texture_a{ texture_a.clone() },
                  m_texture_b{ texture_b.clone() }
        {}

        // Standard Constructor (Colors)
        Pattern(const Matrix3& transform_matrix, const Color& color_a, const Color& color_b)
                : Texture{ transform_matrix },
                  m_texture_a{ ColorTexture{ color_a }.clone() },
                  m_texture_b{ ColorTexture{ color_b }.clone() }
        {}

        /* Destructor */

        ~Pattern() override = default;

        /* Accessors */

        [[nodiscard]] const Texture& getTextureA() const
        { return *m_texture_a; }

        [[nodiscard]] const Texture& getTextureB() const
        { return *m_texture_b; }

    private:
        /* Data Members */

        std::shared_ptr<Texture> m_texture_a{ };
        std::shared_ptr<Texture> m_texture_b{ };
    };
}
