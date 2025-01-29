#include "ray.hpp"

#include <cmath>

namespace gfx {
    // Equality Operator
    bool Ray::operator==(const Ray& rhs) const
    {
        return
                m_origin == rhs.getOrigin() &&
                m_direction == rhs.getDirection();
    }

    // Ray-Sphere Intersection Calculator
    std::vector<Intersection> Ray::getIntersections(const Sphere& sphere) const
    {
        // Transform the ray to the object space of the sphere
        const Ray transformed_ray{ this->transform(sphere.getTransform().inverse()) };

        // Get the distance from the origin to the center of the sphere
        const Vector4 sphere_center{ createPoint(0, 0, 0) };
        const Vector4 sphere_center_distance{ transformed_ray.getOrigin() - sphere_center };

        // Calculate the discriminant of the polynomial whose solutions are the intersections with the sphere
        const double a{ dotProduct(transformed_ray.getDirection(), transformed_ray.getDirection()) };
        const double b{ 2 * dotProduct(transformed_ray.getDirection(), sphere_center_distance) };
        const double c{ dotProduct(sphere_center_distance, sphere_center_distance) - 1 };
        const double discriminant{ std::powf(b, 2) - 4 * a * c };

        // No Solutions, return empty vector
        if (discriminant < 0) {
            return std::vector<Intersection> { };
        }
        // One Solution, return vector with intersection distance listed twice
        else if (discriminant == 0) {
            const Intersection intersection{ -b / (2 * a),
                                             sphere };
            return std::vector<Intersection>{ intersection, intersection };
        }
        // Two Solutions, return vector with intersection distances
        else {
            const Intersection intersection_a{ (-b - std::sqrt(discriminant)) / (2 * a),
                                               sphere };
            const Intersection intersection_b{ (-b + std::sqrt(discriminant)) / (2 * a),
                                               sphere };
            return std::vector<Intersection>{ intersection_a, intersection_b };
        }
    }

    // Transform Ray
    Ray Ray::transform(const Matrix4& transform_matrix) const
    {
        return Ray{ transform_matrix * m_origin,
                    transform_matrix * m_direction };
    }
}