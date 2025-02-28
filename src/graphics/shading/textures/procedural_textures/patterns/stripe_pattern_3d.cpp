#include "stripe_pattern_3d.hpp"

#include <cmath>

namespace gfx {
    Color StripePattern3D::sample3DTextureAt(const Vector4& transformed_point, const TextureMap& mapping) const
    {
        if (static_cast<int>(std::floor(transformed_point.x())) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_point, mapping);

        return this->getTextureB().getTextureColorAt(transformed_point, mapping);
    }

    bool StripePattern3D::areEquivalent(const Texture& other_texture) const
    {
        const StripePattern3D& other_stripe_pattern{ dynamic_cast<const StripePattern3D&>(other_texture) };
        return
            this->getTransform() == other_stripe_pattern.getTransform() &&
            this->getTextureA() == other_stripe_pattern.getTextureA() &&
            this->getTextureB() == other_stripe_pattern.getTextureB();
    }
}