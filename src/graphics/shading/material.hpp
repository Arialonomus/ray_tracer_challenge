#pragma once

#include "color.hpp"

namespace gfx {
    class Material {
    public:
        /* Constructors */

        Material() = default;
        Material(const Color& color,
                 const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
                : m_color{ color },
                m_ambient{ ambient },
                m_diffuse{ diffuse },
                m_specular{ specular },
                m_shininess{ shininess }
        {}
        Material(const float color_r,
                 const float color_g,
                 const float color_b,
                 const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
                : m_color{ Color{ color_r, color_g, color_b } },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}
        explicit Material(const Color& color)
                : m_color{ color },
                  m_ambient{ 0.1 },
                  m_diffuse{ 0.9 },
                  m_specular{ 0.9 },
                  m_shininess{ 200 }
        {}
        Material(const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
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
        [[nodiscard]] double getAmbient() const { return m_ambient; }
        [[nodiscard]] double getDiffuse() const { return m_diffuse; }
        [[nodiscard]] double getSpecular() const { return m_specular; }
        [[nodiscard]] double getShininess() const { return m_shininess; }

        /* Mutators */

        void setColor(const Color& color) { m_color = color; }
        void setColor(const float r, const float g, const float b) { m_color.setValues(r, g, b); }
        void setAmbient(const double ambient) { m_ambient = ambient; }
        void setDiffuse(const double diffuse) { m_diffuse = diffuse; }
        void setSpecular(const double specular) { m_specular = specular; }
        void setShininess(const double shininess) { m_shininess = shininess; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Material& rhs) const;

    private:
        /* Data Members */

        Color m_color{ 1, 1, 1 };
        double m_ambient{ 0.1 };
        double m_diffuse{ 0.9 };
        double m_specular{ 0.9 };
        double m_shininess{ 200 };
    };
}
