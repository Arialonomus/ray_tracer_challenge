#include "ring_pattern_3d.hpp"

#include <cmath>

namespace gfx {
    Color RingPattern3D::sample3DTextureAt(const Vector4& transformed_point, const TextureMap& mapping) const
    {
        const double radius{ std::sqrt(std::pow(transformed_point.x(), 2) + std::pow(transformed_point.z(), 2)) };
        if (static_cast<int>(std::floor(radius)) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_point, mapping);

        return this->getTextureB().getTextureColorAt(transformed_point, mapping);
    }

    bool RingPattern3D::areEquivalent(const Texture& other_texture) const
    {
        const RingPattern3D& other_ring_pattern{ dynamic_cast<const RingPattern3D&>(other_texture) };
        return
                this->getTransform() == other_ring_pattern.getTransform() &&
                this->getTextureA() == other_ring_pattern.getTextureA() &&
                this->getTextureB() == other_ring_pattern.getTextureB();
    }
}