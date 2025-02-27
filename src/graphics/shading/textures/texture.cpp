#include "texture.hpp"

namespace gfx {
    Color Texture::getTextureColorAt(const Vector3& uv_coordinate) const
    {
        const Vector3 transformed_uv_coordinate{ m_transform_inverse * uv_coordinate };
        return sampleTextureAt(transformed_uv_coordinate);
    }
}