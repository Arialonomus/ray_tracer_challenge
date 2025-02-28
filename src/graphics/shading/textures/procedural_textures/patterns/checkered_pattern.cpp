#include "checkered_pattern.hpp"

#include <cmath>

namespace gfx {
    Color CheckeredPattern::sample3DTextureAt(const Vector4& transformed_point, const TextureMap& mapping) const
    {
        if (static_cast<int>(
                std::floor(transformed_point.x()) +
                std::floor(transformed_point.y()) +
                std::floor(transformed_point.z())
                ) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_point, mapping);

        return this->getTextureB().getTextureColorAt(transformed_point, mapping);
    }

    bool CheckeredPattern::areEquivalent(const Texture& other_texture) const
    {
        const CheckeredPattern& other_checkered_pattern{ dynamic_cast<const CheckeredPattern&>(other_texture) };
        return
                this->getTransform() == other_checkered_pattern.getTransform() &&
                this->getTextureA() == other_checkered_pattern.getTextureA() &&
                this->getTextureB() == other_checkered_pattern.getTextureB();
    }
}