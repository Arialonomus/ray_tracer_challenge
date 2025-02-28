#include "stripe_pattern.hpp"

#include <cmath>

namespace gfx {
    Color StripePattern::sample3DTextureAt(const Vector4& transformed_point, const TextureMap& mapping) const
    {
        if (static_cast<int>(std::floor(transformed_point.x())) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_point, mapping);

        return this->getTextureB().getTextureColorAt(transformed_point, mapping);
    }

    bool StripePattern::areEquivalent(const Texture& other_texture) const
    {
        const StripePattern& other_stripe_pattern{ dynamic_cast<const StripePattern&>(other_texture) };
        return
            this->getTransform() == other_stripe_pattern.getTransform() &&
            this->getTextureA() == other_stripe_pattern.getTextureA() &&
            this->getTextureB() == other_stripe_pattern.getTextureB();
    }
}