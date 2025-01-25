#pragma once

#include "matrix4.hpp"
#include "vector4.hpp"
#include "material.hpp"

namespace gfx {
    class Sphere
    {
    public:
        /* Constructors */

        Sphere() = default;
        Sphere(const Matrix4& transform, const Material& material)
                : m_transform{ transform }, m_material{ material }
        {}
        Sphere(const Matrix4& transform)
                : m_transform{ transform }, m_material{ }
        {}
        Sphere(const Material& material)
                : m_transform{ gfx::createIdentityMatrix() }, m_material{ material }
        {}
        Sphere(const Sphere&) = default;
        Sphere(const Sphere&&) = default;

        /* Destructor */

        ~Sphere() = default;

        /* Assignment Operators */

        Sphere& operator=(const Sphere&) = default;
        Sphere& operator=(Sphere&&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Sphere& rhs) const;

        /* Accessors */

        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }
        [[nodiscard]] const Material& getMaterial() const
        { return m_material; }

        /* Mutators */

        void setTransform(const Matrix4& transform_matrix)
        { m_transform = transform_matrix; }
        void setMaterial(const Material& material)
        { m_material = material; }

        /* Geometric Operations */

        // Returns the surface normal vector at a passed-in world_point
        [[nodiscard]] Vector4 getSurfaceNormal(const Vector4& world_point) const;

    private:
        Matrix4 m_transform{ gfx::createIdentityMatrix() };
        Material m_material{ };
    };
}
