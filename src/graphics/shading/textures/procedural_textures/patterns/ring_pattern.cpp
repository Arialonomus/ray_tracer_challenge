#include "ring_pattern.hpp"

#include <cmath>

namespace gfx {
    Color RingPattern::sampleTextureAt(const Vector3& transformed_uv) const
    {
        const double radius{ std::sqrt(std::pow(transformed_uv.x(), 2) + std::pow(transformed_uv.y(), 2)) };
        if (static_cast<int>(std::floor(radius)) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_uv);

        return this->getTextureB().getTextureColorAt(transformed_uv);
    }

    bool RingPattern::areEquivalent(const Texture& other_texture) const
    {
        const RingPattern& other_ring_pattern{ dynamic_cast<const RingPattern&>(other_texture) };
        return
                this->getTransform() == other_ring_pattern.getTransform() &&
                this->getTextureA() == other_ring_pattern.getTextureA() &&
                this->getTextureB() == other_ring_pattern.getTextureB();
    }
}