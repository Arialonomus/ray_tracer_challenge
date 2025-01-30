#include "plane.hpp"

namespace gfx {
// Equality Operator
    bool Plane::operator==(const Plane& rhs) const
    {
        return this->getTransform() == rhs.getTransform() && this->getMaterial() == rhs.getMaterial();
    }

    // Surface Normal for a Plane
    Vector4 Plane::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ 0, 1, 0, 0 };
    }

    // Ray-Plane Intersection Calculator
    std::vector<Intersection> Plane::calculateIntersections(const Ray& transformed_ray) const
    {
        return std::vector<Intersection>{ };
    }
}