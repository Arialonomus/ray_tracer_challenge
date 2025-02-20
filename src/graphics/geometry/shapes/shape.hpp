#pragma once

#include "object.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "material.hpp"

namespace gfx {
    class Shape : public Object
    {
    public:
        /* Constructors */

        // Default Constructor
        Shape() = default;

        // Transform-Only Constructor
        explicit Shape(const Matrix4& transform)
                : Object(transform), m_material{ }
        {}

        // Material-Only Constructor
        explicit Shape(Material material)
                : Object(), m_material{ std::move(material) }
        {}

        // Standard Constructor
        Shape(const Matrix4& transform, Material material)
                : Object(transform), m_material{ std::move(material) }
        {}

        // Copy Constructor
        Shape(const Shape&) = default;

        /* Destructor */

        ~Shape() override = default;

        /* Assignment Operators */

        Shape& operator=(const Shape&) = default;

        /* Accessors */

        [[nodiscard]] const Material& getMaterial() const
        { return m_material; }

        [[nodiscard]] Color getObjectColorAt(const Vector4& world_point) const;

        /* Mutators */

        void setMaterial(const Material& material)
        { m_material = material; }

        /* Geometric Operations */

        // Returns the surface normal vector at a passed-in world_point
        [[nodiscard]] Vector4 getSurfaceNormalAt(const Vector4& world_point) const;

    private:
        /* Data Members */

        Material m_material{ };

        /* Pure Virtual Helper Methods */

        [[nodiscard]] virtual Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const = 0;
    };
}
