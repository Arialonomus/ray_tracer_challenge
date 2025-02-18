#include "plane.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
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

    // Plane Object Equivalency Check
    bool Plane::areEquivalent(const Shape& other_shape) const
    {
        const Plane& other_plane{ dynamic_cast<const Plane&>(other_shape) };

        return
                this->getTransform() == other_plane.getTransform() &&
                this->getMaterial() == other_plane.getMaterial();
    }
}