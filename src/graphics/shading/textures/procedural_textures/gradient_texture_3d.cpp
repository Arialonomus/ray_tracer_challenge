#include "gradient_texture_3d.hpp"

#include <cmath>

namespace gfx {
    Color GradientTexture3D::sample3DTextureAt(const Vector4& transformed_point, const TextureMap& mapping) const
    {
        return m_color_a + (m_color_b - m_color_a) * (transformed_point.x() - std::floor(transformed_point.x()));
    }

    bool GradientTexture3D::areEquivalent(const Texture& other_texture) const
    {
        const GradientTexture3D& other_gradient_texture{ dynamic_cast<const GradientTexture3D&>(other_texture) };
        return
                this->getTransform() == other_gradient_texture.getTransform() &&
                this->getColorA() == other_gradient_texture.getColorA() &&
                this->getColorB() == other_gradient_texture.getColorB();
    }
}