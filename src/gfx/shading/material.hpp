#pragma once

#include "color.hpp"

namespace gfx {
    class Material {
    public:
        Material() = default;
        Material(const Color& color,
                 const float ambient,
                 const float diffuse,
                 const float specular,
                 const float shininess)
                : m_color{ color },
                m_ambient{ ambient },
                m_diffuse{ diffuse },
                m_specular{ specular },
                m_shininess{ shininess }
        {}
        Material(const float color_r,
                 const float color_g,
                 const float color_b,
                 const float ambient,
                 const float diffuse,
                 const float specular,
                 const float shininess)
                : m_color{ Color{ color_r, color_g, color_b } },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}
        Material(const Color& color)
                : m_color{ color },
                  m_ambient{ 0.1 },
                  m_diffuse{ 0.9 },
                  m_specular{ 0.9 },
                  m_shininess{ 200 }
        {}
        Material(const float ambient,
                 const float diffuse,
                 const float specular,
                 const float shininess)
                : m_color{ 1, 1, 1 },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}
        Material(const Material&) = default;
        Material(Material&&) = default;

        /* Destructor */

        virtual ~Material() = default;

        /* Assignment Operators */

        Material& operator=(const Material&) = default;
        Material& operator=(Material&&) = default;

        /* Accessors */

        [[nodiscard]] const Color& getColor() const { return m_color; }
        [[nodiscard]] float getAmbient() const { return m_ambient; }
        [[nodiscard]] float getDiffuse() const { return m_diffuse; }
        [[nodiscard]] float getSpecular() const { return m_specular; }
        [[nodiscard]] float getShininess() const { return m_shininess; }

        /* Mutators */

        const void setColor(const Color& color) { m_color = color; }
        const void setColor(const float r, const float g, const float b) { m_color.setValues(r, g, b); }
        const void setAmbient(const float ambient) { m_ambient = ambient; }
        const void setDiffuse(const float diffuse) { m_diffuse = diffuse; }
        const void setSpecular(const float specular) { m_specular = specular; }
        const void setShininess(const float shininess) { m_shininess = shininess; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Material& rhs) const;

    private:
        Color m_color{ 1, 1, 1 };
        float m_ambient{ 0.1 };
        float m_diffuse{ 0.9 };
        float m_specular{ 0.9 };
        float m_shininess{ 200 };
    };
}
