#pragma once

#include "pattern_tex.hpp"

namespace gfx {
    class GradientTexture : public Texture
    {
    public:
        /* Constructors */

        // Default Constructor
        GradientTexture() = delete;

        // Color-Only Constructor
        GradientTexture(const Color& color_a, const Color& color_b)
                : Texture{ }, m_color_a{ color_a }, m_color_b{ color_b }
        {}

        // Standard Constructor
        GradientTexture(const Matrix3& transform_matrix, const Color& color_a, const Color& color_b)
                : Texture{ transform_matrix }, m_color_a{ color_a }, m_color_b{ color_b }
        {}

        /* Destructor */

        ~GradientTexture() override = default;

        /* Accessors */

        [[nodiscard]] const Color& getColorA() const
        { return m_color_a; }

        [[nodiscard]] const Color& getColorB() const
        { return m_color_b; }

        /* Object Operations */

        [[nodiscard]] std::shared_ptr<Texture> clone() const override
        { return std::make_shared<GradientTexture>(*this); }

    private:
        /* Data Members */

        Color m_color_a;
        Color m_color_b;

        /* Texture Helper Method Overrides */

        [[nodiscard]] Color sampleTextureAt(const Vector3& transformed_uv) const override;
        [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override;
    };
}
