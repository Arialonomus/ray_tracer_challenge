#include "cube.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Cube::operator==(const Cube& rhs) const
    {
        return this->getTransform() == rhs.getTransform() && this->getMaterial() == rhs.getMaterial();
    }

    // Surface Normal for a Cube
    Vector4 Cube::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ };
    }

    // Ray-Cube Intersection Calculator
    std::vector<Intersection> Cube::calculateIntersections(const Ray& transformed_ray) const
    {
        return std::vector<Intersection>{ };
    }
}