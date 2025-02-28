#pragma once

#include <memory>

#include "color.hpp"
#include "texture.hpp"
#include "color_texture.hpp"

namespace gfx {
    struct MaterialProperties {
        double ambient{ 0.1 };
        double diffuse{ 0.9 };
        double specular{ 0.9 };
        double shininess{ 200 };
        double reflectivity{ 0 };
        double transparency{ 0 };
        double refractive_index{ 1 };

        bool operator==(const MaterialProperties& rhs) const;
    };

    class Material
    {
    public:
        /* Constructors */

        // Default Constructor
        Material() = default;

        // Color Constructor (Color Object)
        explicit Material(const Color& color, const MaterialProperties properties = MaterialProperties{ })
                : m_texture{ ColorTexture{ color }.clone() },
                  m_properties{ properties }
        {}

        // Color Constructor (Float List)
        explicit Material(const double color_r, const double color_g, const double color_b,
                 const MaterialProperties properties = MaterialProperties{ })
                : m_texture{ ColorTexture{ color_r, color_g, color_b }.clone() },
                  m_properties{ properties }
        {}

        // Texture Constructor
        explicit Material(const Texture& texture, const MaterialProperties properties = MaterialProperties{ })
                : m_texture{ texture.clone() },
                  m_properties{ properties }
        {}

        // Properties-Only Constructor
        explicit Material(const MaterialProperties properties)
                : m_texture{ ColorTexture{ }.clone() },
                  m_properties{ properties }
        {}

        // Copy Constructor
        Material(const Material& src)
                : m_texture{ src.m_texture->clone() },
                  m_properties{ src.m_properties }
        {}

        // Move Constructor
        Material(Material&& src) noexcept
                : m_texture{ std::move(src.m_texture) },
                  m_properties{ src.m_properties }
        {}

        /* Destructor */

        ~Material() = default;

        /* Assignment Operators */

        // Copy Assignment Operator
        Material& operator=(const Material& rhs)
        {
            if (this == &rhs)
                return *this;

            m_texture = rhs.m_texture->clone();
            m_properties = rhs.m_properties;

            return *this;
        }

        // Move Assignment Operator
        Material& operator=(Material&& rhs) noexcept
        {
            if (rhs == *this)
                return *this;

            m_texture = std::move(rhs.m_texture);
            m_properties = rhs.m_properties;

            return *this;
        }

        /* Accessors */

        [[nodiscard]] const Texture& getTexture() const
        { return *m_texture; }

        [[nodiscard]] const MaterialProperties& getProperties() const
        { return m_properties; }

        /* Mutators */

        void setTexture(const Texture& texture)
        { m_texture = texture.clone(); }

        void setTexture(const std::shared_ptr<Texture>& texture_ptr)
        { m_texture = texture_ptr->clone(); }

        void setTexture(std::shared_ptr<Texture>&& texture_ptr)
        { m_texture = std::move(texture_ptr); }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Material& rhs) const;

    private:
        /* Data Members */

        std::shared_ptr<Texture> m_texture{ ColorTexture{ }.clone() };
        MaterialProperties m_properties{ };
    };

    /* Material Factory Functions */

    // Returns a new Material object with transparency and refractive index set to those of clear glass
    [[nodiscard]] Material createGlassyMaterial();
}
