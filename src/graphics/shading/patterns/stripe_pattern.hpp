#pragma once

#include "two_tone_pattern.hpp"

namespace gfx {
    class StripePattern : public TwoTonePattern
    {
    public:
        /* Constructors */

        // Default Constructor
        StripePattern() = delete;

        // Color-Only Constructor
        StripePattern(const Color& color_a, const Color& color_b)
                : TwoTonePattern{ color_a, color_b }
        {}

        // Standard Constructor
        StripePattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : TwoTonePattern{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~StripePattern() override = default;

        /* Accessors */

        [[nodiscard]] Color samplePatternAt(const Vector4& pattern_point) const override;

        /* Object Operations */

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override
        { return std::make_unique<StripePattern>(*this); }

    private:
        /* Helper Methods */

        [[nodiscard]] bool equal(const Pattern& other) const override;
    };
}
