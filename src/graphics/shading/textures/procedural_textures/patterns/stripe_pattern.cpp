#include "stripe_pattern.hpp"

#include <cmath>

namespace gfx {
    Color StripePattern::sampleTextureAt(const Vector3& transformed_uv) const
    {
        if (static_cast<int>(std::floor(transformed_uv.x())) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_uv);

        return this->getTextureB().getTextureColorAt(transformed_uv);
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