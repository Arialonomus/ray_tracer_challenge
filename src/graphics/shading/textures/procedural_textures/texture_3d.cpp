#include "texture_3d.hpp"

namespace gfx {
    Color Texture3D::getTextureColorAt(const Vector4& object_point,
                                       const TextureMap& mapping) const
    {
        const Vector4 transformed_point{ m_transform_inverse * object_point };
        return sample3DTextureAt(transformed_point, mapping);
    }
}