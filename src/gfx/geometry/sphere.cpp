#include "sphere.hpp"

namespace gfx {
    // Equality Operator
    bool Sphere::operator==(const Sphere& rhs) const
    {
        return m_transform == rhs.getTransform();
    }

    // Surface Normal at a Point
    Vector4 Sphere::getSurfaceNormal(const Vector4& world_point) const
    {
        // Transform the point from world space to object space
        const Matrix4 transform_inverse{ m_transform.inverse() };
        const Vector4 object_point{ transform_inverse * world_point };

        // Calculate the normal and transform the normal vector back to world space
        const Vector4 object_normal{ object_point - createPoint(0, 0, 0) };
        Vector4 world_normal{ transform_inverse.transpose() * object_normal };

        // Reset the w-value in case the shape's transformation matrix included a translation
        world_normal.resetW();

        return normalize(world_normal);
    }
}