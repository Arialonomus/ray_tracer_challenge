#include "intersection.hpp"

#include "util_functions.hpp"

namespace gfx {
    bool Intersection::operator==(const Intersection& rhs) const
    {
        return utils::areEqual(m_t, rhs.getT()) && m_object_ptr == &rhs.getObject();
    }

    DetailedIntersection::DetailedIntersection(const Intersection& intersection, const Ray& ray)
            : Intersection(intersection),
              m_intersection_position{ ray.position(intersection.getT()) },
              m_surface_normal{ intersection.getObject().getSurfaceNormalAt(m_intersection_position) },
              m_view_vector{ -ray.getDirection() },
              m_reflection_vector{ },
              m_over_point{ },
              m_under_point{ },
              m_is_inside_object{ false }
    {
        // Use the angle between the normal and the view vector to determine if origin is inside the object
        if (utils::isLess(dotProduct(m_surface_normal, m_view_vector), 0.0)) {
            m_is_inside_object = true;
            m_surface_normal = -m_surface_normal;
        }

        // Calculate the reflection vector from the surface normal
        m_reflection_vector = ray.getDirection().reflect(m_surface_normal);

        // Calculate a point slightly above the object surface for use in shadow calculations
        m_over_point = m_intersection_position + m_surface_normal * utils::EPSILON;

        // Calculate a point slightly below the object surface for use in refraction calculations
        m_under_point = m_intersection_position - m_surface_normal * utils::EPSILON;
    }

    std::optional<Intersection> getHit(std::vector<Intersection> intersections)
    {
        auto hit_iter = std::lower_bound(
                intersections.begin(),
                intersections.end(),
                0.0f);
        if (hit_iter != intersections.end()) {
            return *hit_iter;
        } else {
            return std::nullopt;
        }
    }
}