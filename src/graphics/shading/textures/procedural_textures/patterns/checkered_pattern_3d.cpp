#include "checkered_pattern_3d.hpp"

#include <cmath>

namespace gfx {
    Color CheckeredPattern3D::sample3DTextureAt(const Vector4& transformed_point, const TextureMap& mapping) const
    {
        if (static_cast<int>(
                std::floor(transformed_point.x()) +
                std::floor(transformed_point.y()) +
                std::floor(transformed_point.z())
                ) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_point, mapping);

        return this->getTextureB().getTextureColorAt(transformed_point, mapping);
    }

    bool CheckeredPattern3D::areEquivalent(const Texture& other_texture) const
    {
        const CheckeredPattern3D& other_checkered_pattern{ dynamic_cast<const CheckeredPattern3D&>(other_texture) };
        return
                this->getTransform() == other_checkered_pattern.getTransform() &&
                this->getTextureA() == other_checkered_pattern.getTextureA() &&
                this->getTextureB() == other_checkered_pattern.getTextureB();
    }
}