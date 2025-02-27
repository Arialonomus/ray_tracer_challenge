#include "checkered_pattern.hpp"

#include <cmath>

namespace gfx {
    Color CheckeredPattern::sampleTextureAt(const Vector3& transformed_uv) const
    {
        if (static_cast<int>(std::floor(transformed_uv.x()) + std::floor(transformed_uv.y())) % 2 == 0)
            return this->getTextureA().getTextureColorAt(transformed_uv);

        return this->getTextureB().getTextureColorAt(transformed_uv);
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