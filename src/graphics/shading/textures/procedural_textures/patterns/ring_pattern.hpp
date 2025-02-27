#pragma once

#include "pattern.hpp"

namespace gfx {
    class RingPattern : public Pattern
    {
    public:
        /* Constructors */

        // Default Constructor
        RingPattern() = delete;

        // Texture-Only Constructor
        RingPattern(const Texture& texture_a, const Texture& texture_b)
                : Pattern{ texture_a, texture_b }
        {}

        // Color-Only Constructor
        RingPattern(const Color& color_a, const Color& color_b)
                : Pattern{ color_a, color_b }
        {}

        // Standard Constructor (Textures)
        RingPattern(const Matrix3& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : Pattern{ transform_matrix, texture_a, texture_b }
        {}

        // Standard Constructor (Colors)
        RingPattern(const Matrix3& transform_matrix, const Color& color_a, const Color& color_b)
                : Pattern{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~RingPattern() override = default;

        /* Object Operations */

        [[nodiscard]] std::shared_ptr<Texture> clone() const override
        { return std::make_shared<RingPattern>(*this); }

    private:
        /* Texture Helper Method Overrides */

        [[nodiscard]] Color sampleTextureAt(const Vector3& transformed_uv) const override;
        [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override;
    };
}
