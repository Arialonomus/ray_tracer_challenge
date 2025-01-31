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

        // Returns the color for this pattern at a passed-in point
        [[nodiscard]] Color samplePatternAt(const Vector4& pattern_point) const override;

        /* Object Operations */

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override
        { return std::make_unique<StripePattern>(*this); }

    private:
        /* Data Members */

        Color m_color_a{};
        Color m_color_b{};

        /* Helper Methods */
        [[nodiscard]] bool equal(const Pattern& other) const override;
    };
}
