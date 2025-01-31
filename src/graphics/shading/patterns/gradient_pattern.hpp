#pragma once

#include "two_tone_pattern.hpp"

namespace gfx {
    class GradientPattern : public TwoTonePattern
    {
    public:
        /* Constructors */

        // Default Constructor
        GradientPattern() = delete;

        // Color-Only Constructor
        GradientPattern(const Color& color_a, const Color& color_b)
                : TwoTonePattern{ color_a, color_b }
        {}

        // Standard Constructor
        GradientPattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : TwoTonePattern{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~GradientPattern() override = default;

        /* Accessors */

        [[nodiscard]] Color samplePatternAt(const Vector4& pattern_point) const override;

        /* Object Operations */

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override
        { return std::make_unique<GradientPattern>(*this); }

    private:
        /* Helper Methods */

        [[nodiscard]] bool equal(const Pattern& other) const override;
    };
}
