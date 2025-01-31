#pragma once

#include "pattern.hpp"

namespace gfx {
    class StripePattern : public Pattern
    {
    public:
        /* Constructors */

        StripePattern() = delete;
        StripePattern(const Color& color_a, const Color& color_b)
                : Pattern{ }, m_color_a{ color_a }, m_color_b{ color_b }
        {}
        StripePattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : Pattern{ transform_matrix }, m_color_a{ color_a }, m_color_b{ color_b }
        {}

        /* Destructor */

        ~StripePattern() override = default;

        /* Accessors */

        [[nodiscard]] const Color& getColorA() const
        { return m_color_a; }
        [[nodiscard]] const Color& getColorB() const
        { return m_color_b; }

        // Returns the surface color for this pattern at a passed-in point
        [[nodiscard]] Color getSurfaceColorAt(const Vector4& point) const override;

    private:
        Color m_color_a{};
        Color m_color_b{};
    };
}
