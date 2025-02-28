#pragma once

#include "pattern_texture_3d.hpp"

namespace gfx {
    class StripePattern3D : public PatternTexture3D
    {
    public:
        /* Constructors */

        // Default Constructor
        StripePattern3D() = delete;

        // Texture-Only Constructor
        StripePattern3D(const Texture& texture_a, const Texture& texture_b)
                : PatternTexture3D{ texture_a, texture_b }
        {}

        // Color-Only Constructor
        StripePattern3D(const Color& color_a, const Color& color_b)
                : PatternTexture3D{ color_a, color_b }
        {}

        // Standard Constructor (Textures)
        StripePattern3D(const Matrix4& transform_matrix, const Texture& texture_a, const Texture& texture_b)
                : PatternTexture3D{ transform_matrix, texture_a, texture_b }
        {}

        // Standard Constructor (Colors)
        StripePattern3D(const Matrix4& transform_matrix, const Color& color_a, const Color& color_b)
                : PatternTexture3D{ transform_matrix, color_a, color_b }
        {}

        /* Destructor */

        ~StripePattern3D() override = default;

        /* Object Operations */

        [[nodiscard]] std::shared_ptr<Texture> clone() const override
        { return std::make_shared<StripePattern3D>(*this); }

    private:
        /* Texture Helper Method Overrides */

        [[nodiscard]] Color sample3DTextureAt(const Vector4& transformed_point,
                                              const TextureMap& mapping) const override;
        [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override;
    };
}
