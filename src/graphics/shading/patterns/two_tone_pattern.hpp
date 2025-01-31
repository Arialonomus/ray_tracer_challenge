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

    private:
        /* Data Members */

        Color m_color_a{ };
        Color m_color_b{ };
    };
}
