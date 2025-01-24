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
        // Get the distance from the origin to the center of the sphere
        const Vector4 sphere_center{ createPoint(0, 0, 0) };
        const Vector4 sphere_center_distance{ m_origin - sphere_center };

        // Calculate the discriminant of the polynomial whose solutions are the intersections with the sphere
        const float a{ dotProduct(m_direction, m_direction) };
        const float b{ 2 * dotProduct(m_direction, sphere_center_distance) };
        const float c{ dotProduct(sphere_center_distance, sphere_center_distance) - 1 };
        const float discriminant{ std::powf(b, 2) - 4 * a * c };

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
}