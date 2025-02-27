#include "gradient_texture.hpp"

#include <cmath>

namespace gfx {
    Color GradientTexture::sampleTextureAt(const Vector3& transformed_uv) const
    {
        return m_color_a + (m_color_b - m_color_a) * (transformed_uv.x() - std::floor(transformed_uv.x()));
    }

    bool GradientTexture::areEquivalent(const Texture& other_texture) const
    {
        const GradientTexture& other_gradient_texture{ dynamic_cast<const GradientTexture&>(other_texture) };
        return
                this->getTransform() == other_gradient_texture.getTransform() &&
                this->getColorA() == other_gradient_texture.getColorA() &&
                this->getColorB() == other_gradient_texture.getColorB();
    }
}