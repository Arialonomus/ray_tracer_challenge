#pragma once

#include <memory>

#include "color.hpp"
#include "pattern.hpp"

namespace gfx {
    class Material
    {
    public:
        /* Constructors */

        // Default Constructor
        Material() = default;

        // Color-Only Constructor
        explicit Material(const Color& color)
                : m_color{ color },
                  m_pattern{ nullptr },
                  m_ambient{ 0.1 },
                  m_diffuse{ 0.9 },
                  m_specular{ 0.9 },
                  m_shininess{ 200 }
        {}

        // Pattern-Only Constructor
        explicit Material(const Pattern& pattern)
                : m_color{ 1, 1, 1 },
                  m_pattern{ pattern.clone() },
                  m_ambient{ 0.1 },
                  m_diffuse{ 0.9 },
                  m_specular{ 0.9 },
                  m_shininess{ 200 }
        {}

        // Phong Values-Only Constructor
        Material(const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
                : m_color{ 1, 1, 1 },
                  m_pattern{ nullptr },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}

        // No-Pattern Constructor (Color Object)
        Material(const Color& color,
                 const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
                : m_color{ color },
                  m_pattern{ nullptr },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}

        // No-Pattern Constructor (Float List)
        Material(const double color_r,
                 const double color_g,
                 const double color_b,
                 const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
                : m_color{ Color{ color_r, color_g, color_b }},
                  m_pattern{ nullptr },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}

        // No-Color Constructor
        Material(const Pattern& pattern,
                 const double ambient,
                 const double diffuse,
                 const double specular,
                 const double shininess)
                : m_color{ 1, 1, 1 },
                  m_pattern{ pattern.clone() },
                  m_ambient{ ambient },
                  m_diffuse{ diffuse },
                  m_specular{ specular },
                  m_shininess{ shininess }
        {}

        // Copy Constructor
        Material(const Material& src)
                : m_color{ src.m_color },
                  m_pattern{ src.m_pattern ? src.m_pattern->clone() : nullptr },
                  m_ambient{ src.m_ambient },
                  m_diffuse{ src.m_diffuse },
                  m_specular{ src.m_specular },
                  m_shininess{ src.m_shininess }
        {}

        // Move Constructor
        Material(Material&& src)
                : m_color{ std::move(src.m_color) },
                  m_pattern{ std::move(src.m_pattern) },
                  m_ambient{ src.m_ambient },
                  m_diffuse{ src.m_diffuse },
                  m_specular{ src.m_specular },
                  m_shininess{ src.m_shininess }
        {}

        /* Destructor */

        ~Material() = default;

        /* Assignment Operators */

        // Copy Assignment Operator
        Material& operator=(const Material& src)
        {
            m_color = src.m_color;
            m_pattern = src.m_pattern ? src.m_pattern->clone() : nullptr;
            m_ambient = src.m_ambient;
            m_diffuse = src.m_diffuse;
            m_specular = src.m_specular;
            m_shininess = src.m_shininess;

            return *this;
        }

        // Move Assignment Operator
        Material& operator=(Material&& src)
        {
            m_color = std::move(src.m_color);
            m_pattern = std::move(src.m_pattern);
            m_ambient = src.m_ambient;
            m_diffuse = src.m_diffuse;
            m_specular = src.m_specular;
            m_shininess = src.m_shininess;

            return *this;
        }

        /* Accessors */

        [[nodiscard]] const Color& getColor() const
        { return m_color; }

        [[nodiscard]] bool hasPattern() const
        { return m_pattern != nullptr; }

        [[nodiscard]] const Pattern& getPattern() const
        { return *m_pattern; }

        [[nodiscard]] double getAmbient() const
        { return m_ambient; }

        [[nodiscard]] double getDiffuse() const
        { return m_diffuse; }

        [[nodiscard]] double getSpecular() const
        { return m_specular; }

        [[nodiscard]] double getShininess() const
        { return m_shininess; }

        /* Mutators */

        void setColor(const Color& color)
        { m_color = color; }

        void setColor(const double r, const double g, const double b)
        { m_color.setValues(r, g, b); }

        void setPattern(const Pattern& pattern);

        void setAmbient(const double ambient)
        { m_ambient = ambient; }

        void setDiffuse(const double diffuse)
        { m_diffuse = diffuse; }

        void setSpecular(const double specular)
        { m_specular = specular; }

        void setShininess(const double shininess)
        { m_shininess = shininess; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Material& rhs) const;

    private:
        /* Data Members */

        Color m_color{ 1, 1, 1 };
        std::unique_ptr<Pattern> m_pattern{ nullptr };
        double m_ambient{ 0.1 };
        double m_diffuse{ 0.9 };
        double m_specular{ 0.9 };
        double m_shininess{ 200 };
    };
}
