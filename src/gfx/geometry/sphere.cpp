#include "sphere.hpp"

namespace gfx {
    // Equality Operator
    bool Sphere::operator==(const Sphere& rhs) const
    {
        return m_transform == rhs.getTransform();
    }

    // Surface Normal at a Point
    Vector4 Sphere::getSurfaceNormal(const Vector4& point) const
    {
        return normalize(point - createPoint(0, 0, 0));
    }
}