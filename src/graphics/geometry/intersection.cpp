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

    std::pair<double, double>
    calculateBoxIntersectionTs(const Ray& ray, const Vector4& box_min_extent, const Vector4& box_max_extent)
    {
        const auto [ x_t_min, x_t_max ] { getAxisIntersectionTs(ray.getOrigin().x(),
                                                                ray.getDirection().x(),
                                                                box_min_extent.x(),
                                                                box_max_extent.x()) };
        const auto [ y_t_min, y_t_max ] { getAxisIntersectionTs(ray.getOrigin().y(),
                                                                ray.getDirection().y(),
                                                                box_min_extent.y(),
                                                                box_max_extent.y()) };
        const auto [ z_t_min, z_t_max ] { getAxisIntersectionTs(ray.getOrigin().z(),
                                                                ray.getDirection().z(),
                                                                box_min_extent.z(),
                                                                box_max_extent.z()) };

        double t_min{ std::fmax( x_t_min, y_t_min ) };
        t_min = std::fmax(t_min, z_t_min);
        double t_max{ std::fmin( x_t_max, y_t_max ) };
        t_max = std::fmin(t_max, z_t_max);

        return std::pair<double, double>{ t_min, t_max };
    }

    std::pair<double, double>
    getAxisIntersectionTs(const double origin_axis_val,
                          const double direction_axis_val,
                          const double min_extent_axis_val,
                          const double max_extent_axis_val)
    {
        double t_min{ (min_extent_axis_val - origin_axis_val) / direction_axis_val };
        double t_max{ (max_extent_axis_val - origin_axis_val) / direction_axis_val };

        if (utils::isGreater(t_min, t_max)) {
            std::swap(t_min, t_max);
        }

        return std::pair<double, double>{ t_min, t_max };
    }
}