#pragma once

#include "pattern.hpp"

namespace gfx {
    class CheckeredPattern : public Pattern
    {
    public:
        /* Constructors */

        // Default Constructor
        CheckeredPattern() = delete;

        // Texture-Only Constructor
        CheckeredPattern(const Texture& texture_a, const Texture& texture_b)
                : Pattern{ texture_a, texture_b }
        {}

        // Color-Only Constructor
        CheckeredPattern(const Color& color_a, const Color& color_b)
                : Pattern{ color_a, color_b }
        {}

        // Standard Constructor (Textures)
        CheckeredPattern(const Matrix4& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : Pattern{ transform_matrix, texture_a, texture_b }
        {}

        // Standard Constructor (Colors)
        CheckeredPattern(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : Pattern{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~CheckeredPattern() override = default;

        /* Object Operations */

        [[nodiscard]] std::shared_ptr<Texture> clone() const override
        { return std::make_shared<CheckeredPattern>(*this); }

    private:
        /* Texture Helper Method Overrides */

        [[nodiscard]] Color sample3DTextureAt(const Vector4& transformed_point,
                                              const TextureMap& mapping) const override;
        [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override;
    };
}
