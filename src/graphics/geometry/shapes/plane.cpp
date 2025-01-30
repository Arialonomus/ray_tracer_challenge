#include "plane.hpp"

#include <cmath>

#include "util_functions.hpp"

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
        const double ray_y_direction = transformed_ray.getDirection().y();

        // Ray is parallel or coplanar to the plane
        if (std::abs(ray_y_direction) < utils::EPSILON) {
            return std::vector<Intersection>{ };
        }

        // Ray intersects plane (assume plane is defined as xz-plane)
        return std::vector<Intersection>{ Intersection{ -transformed_ray.getOrigin().y() / ray_y_direction,
                                                        this } };
    }
}