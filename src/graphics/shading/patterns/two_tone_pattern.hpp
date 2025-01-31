#pragma once

#include "pattern.hpp"

namespace gfx {
    class TwoTonePattern : public Pattern
    {
    public:
        /* Constructors */

        // Default Constructor
        TwoTonePattern() = delete;

        // Color-Only Constructor
        TwoTonePattern(const Color& color_a, const Color& color_b)
                : Pattern{ }, m_color_a{ color_a }, m_color_b{ color_b }
        {}

        // Standard Constructor
        TwoTonePattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : Pattern{ transform_matrix }, m_color_a{ color_a }, m_color_b{ color_b }
        {}

        /* Destructor */

        ~TwoTonePattern() override = default;

        /* Accessors */

        [[nodiscard]] const Color& getColorA() const
        { return m_color_a; }

        [[nodiscard]] const Color& getColorB() const
        { return m_color_b; }

        /* Mutators */

        void setColorA(const Color& color)
        { m_color_a = color; }

        void setColorA(const double r, const double g, const double b)
        { m_color_a.setValues(r, g, b); }

        void setColorB(const Color& color)
        { m_color_b = color; }

        void setColorB(const double r, const double g, const double b)
        { m_color_b.setValues(r, g, b); }

    private:
        /* Data Members */

        Color m_color_a{ };
        Color m_color_b{ };
    };
}
