#pragma once

#include "object.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "material.hpp"
#include "texture_map.hpp"

namespace gfx {
    class Surface : public Object
    {
    public:
        /* Constructors */

        // Default Constructor
        Surface() = default;

        // Transform-Only Constructor
        explicit Surface(const Matrix4& transform, TextureMap texture_mapping = ProjectionMap)
                : Object(transform), m_material{ }, m_texture_mapping{ std::move(texture_mapping) }
        {}

        // Material-Only Constructor
        explicit Surface(Material material, TextureMap texture_mapping = ProjectionMap)
                : Object(), m_material{ std::move(material) }, m_texture_mapping{std::move( texture_mapping )}
        {}

        // Standard Constructor
        Surface(const Matrix4& transform, Material material, TextureMap texture_mapping = ProjectionMap)
                : Object(transform),
                  m_material{ std::move(material) },
                  m_texture_mapping{std::move( texture_mapping )}
        {}

        // Copy Constructor
        Surface(const Surface&) = default;

        /* Destructor */

        ~Surface() override = default;

        /* Assignment Operators */

        Surface& operator=(const Surface&) = default;

        /* Accessors */

        [[nodiscard]] const Material& getMaterial() const;

        [[nodiscard]] const TextureMap& getTextureMapping() const
        { return m_texture_mapping; }

        [[nodiscard]] Vector3 getTextureCoordinateFor(const Vector4& point) const
        { return m_texture_mapping(point); }

        [[nodiscard]] Color getObjectColorAt(const Vector4& world_point) const;

        /* Mutators */

        void setMaterial(const Material& material)
        { m_material = material; }

        void setTextureMap(const TextureMap& texture_mapping)
        { m_texture_mapping = texture_mapping; }

        /* Geometric Operations */

        // Returns the surface normal vector at a passed-in world_point
        [[nodiscard]] Vector4 getSurfaceNormalAt(const Vector4& world_point) const;

    private:
        /* Data Members */

        Material m_material{ };
        TextureMap m_texture_mapping{ ProjectionMap };

        /* Pure Virtual Helper Methods */

        [[nodiscard]] virtual Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const = 0;
    };
}
