#include "procedural_texture.hpp"

namespace gfx {
    Color ProceduralTexture::getTextureColorAt(const Vector4& object_point,
                                               const TextureMap& mapping) const
    {
        const Vector4 transformed_point{ m_transform_inverse * object_point };
        return sample3DTextureAt(transformed_point, mapping);
    }
}