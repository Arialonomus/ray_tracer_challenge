#pragma once

#include "pattern.hpp"

namespace gfx {
    class StripePattern : public Pattern
    {
    public:
        /* Constructors */

        // Default Constructor
        StripePattern() = delete;

        // Texture-Only Constructor
        StripePattern(const Texture& texture_a, const Texture& texture_b)
                : Pattern{ texture_a, texture_b }
        {}

        // Color-Only Constructor
        StripePattern(const Color& color_a, const Color& color_b)
                : Pattern{ color_a, color_b }
        {}

        // Standard Constructor (Textures)
        StripePattern(const Matrix4& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : Pattern{ transform_matrix, texture_a, texture_b }
        {}

        // Standard Constructor (Colors)
        StripePattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : Pattern{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~StripePattern() override = default;

        /* Object Operations */

        [[nodiscard]] std::shared_ptr<Texture> clone() const override
        { return std::make_shared<StripePattern>(*this); }

    private:
        /* Texture Helper Method Overrides */

        [[nodiscard]] Color sample3DTextureAt(const Vector4& transformed_point,
                                              const TextureMap& mapping) const override;
        [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override;
    };
}
