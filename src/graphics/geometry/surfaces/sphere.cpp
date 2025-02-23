#include "sphere.hpp"

#include <cmath>

#include "intersection.hpp"
#include "util_functions.hpp"

namespace gfx {
    // Surface Normal for a Sphere
    Vector4 Sphere::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ transformed_point - createPoint(0, 0, 0) };
    }

    // Ray-Sphere Intersection Calculator
    std::vector<Intersection> Sphere::calculateIntersections(const Ray& transformed_ray) const
    {
        // Get the distance from the origin to the center of the sphere
        const Vector4 sphere_center{ createPoint(0, 0, 0) };
        const Vector4 sphere_center_distance{ transformed_ray.getOrigin() - sphere_center };

        // Calculate the discriminant of the polynomial whose solutions are the intersections with the sphere
        const double a{ dotProduct(transformed_ray.getDirection(), transformed_ray.getDirection()) };
        const double b{ 2 * dotProduct(transformed_ray.getDirection(), sphere_center_distance) };
        const double c{ dotProduct(sphere_center_distance, sphere_center_distance) - 1 };
        const double discriminant{ std::pow(b, 2) - 4 * a * c };

        // No Solutions, return empty vector
        if (utils::isLess(discriminant, 0.0)) {
            return std::vector<Intersection>{};
        }
        // One Solution, return vector with intersection distance listed twice
        else if (utils::areEqual(discriminant, 0.0)) {
            const Intersection intersection{ -b / (2 * a), this };
            return std::vector<Intersection>{ intersection, intersection };
        }
        // Two Solutions, return vector with intersection distances
        else {
            const Intersection intersection_a{ (-b - std::sqrt(discriminant)) / (2 * a), this };
            const Intersection intersection_b{ (-b + std::sqrt(discriminant)) / (2 * a), this };
            return std::vector<Intersection>{ intersection_a, intersection_b };
        }
    }

    // Sphere Object Equivalency Check
    bool Sphere::areEquivalent(const Object& other_object) const
    {
        const Sphere& other_sphere{ dynamic_cast<const Sphere&>(other_object) };

        return
                this->getTransform() == other_sphere.getTransform() &&
                this->getMaterial() == other_sphere.getMaterial();
    }
}