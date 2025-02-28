#pragma once

#include "texture.hpp"

#include "matrix4.hpp"

namespace gfx {
    class Texture3D : public Texture
    {
    public:
        /* Constructors */

        // Default Constructor
        Texture3D() = default;

        // Standard Constructor
        explicit Texture3D(const Matrix4& transform_matrix)
                : Texture(), m_transform{ transform_matrix }, m_transform_inverse{ transform_matrix.inverse() }
        {}

        /* Destructor */

        ~Texture3D() override = default;

        /* Accessors */

        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }

        [[nodiscard]] Color getTextureColorAt(const Vector4& object_point,
                                              const TextureMap& mapping) const override;

    private:
        /* Data Members */

        Matrix4 m_transform{ };
        Matrix4 m_transform_inverse{ };

        /* Helper Methods */

        [[nodiscard]] virtual Color sample3DTextureAt(const Vector4& transformed_point,
                                                      const TextureMap& mapping) const = 0;
    };

}
