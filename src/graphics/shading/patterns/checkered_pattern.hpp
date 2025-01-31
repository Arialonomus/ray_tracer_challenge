#pragma once

#include "two_tone_pattern.hpp"

namespace gfx {
    class CheckeredPattern : public TwoTonePattern
    {
    public:
        /* Constructors */

        // Default Constructor
        CheckeredPattern() = delete;

        // Color-Only Constructor
        CheckeredPattern(const Color& color_a, const Color& color_b)
                : TwoTonePattern{ color_a, color_b }
        {}

        // Standard Constructor
        CheckeredPattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : TwoTonePattern{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~CheckeredPattern() override = default;

        /* Accessors */

        [[nodiscard]] Color samplePatternAt(const Vector4& pattern_point) const override;

        /* Object Operations */

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override
        { return std::make_unique<CheckeredPattern>(*this); }

    private:
        /* Helper Methods */

        [[nodiscard]] bool equal(const Pattern& other) const override;
    };
}
