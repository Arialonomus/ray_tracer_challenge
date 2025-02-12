#include "cylinder.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Cylinder::operator==(const Cylinder& rhs) const
    {
        return this->getTransform() == rhs.getTransform() && this->getMaterial() == rhs.getMaterial();
    }

    // Surface Normal for a Cylinder
    Vector4 Cylinder::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ };
    }

    // Ray-Cylinder Intersection Calculator
    std::vector<Intersection> Cylinder::calculateIntersections(const Ray& transformed_ray) const
    {
        return std::vector<Intersection>{ };
    }
}