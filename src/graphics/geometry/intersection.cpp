#include "intersection.hpp"

#include <algorithm>
#include <list>
#include <unordered_map>

#include "util_functions.hpp"

namespace gfx {
    bool Intersection::operator==(const Intersection& rhs) const
    {
        return utils::areEqual(m_t, rhs.getT()) && m_object_ptr == &rhs.getObject();
    }

    DetailedIntersection::DetailedIntersection(const Intersection& intersection, const Ray& ray)
            : Intersection(intersection),
              m_intersection_position{ ray.position(intersection.getT()) },
              m_surface_normal{ intersection.getObject().getSurfaceNormal(m_intersection_position) },
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
        std::sort(intersections.begin(), intersections.end());
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

    std::pair<double, double> getRefractiveIndices(const Intersection& hit,
                                                   const std::vector<Intersection>& possible_overlaps)
    {
        // The order in which objects are added must be maintained, but we use a map to facilitate quick removal
        // of objects from the list at arbitrary positions without having to repeatedly search the list
        std::list<const Shape*> containing_objects_list{ };
        std::unordered_map<const Shape*, std::list<const Shape*>::iterator> object_list_iterator_map{ };

        // Assume the exited medium is air
        double n1 = 1.0;

        // Check each intersection in the possible overlaps group to find the exited & entered objects
        for (const auto& intersection : possible_overlaps) {
            // The exited medium is an overlapping object
            if (intersection == hit && !containing_objects_list.empty()) {
                n1 = containing_objects_list.back()->getMaterial().getRefractiveIndex();
            }

            const Shape* object_ptr{ &intersection.getObject() };
            if (object_list_iterator_map.contains(object_ptr)) {
                // The ray has exited this object, remove it from the list
                auto list_iter{ object_list_iterator_map[object_ptr] };
                containing_objects_list.erase(list_iter);
                object_list_iterator_map.erase(object_ptr);
            } else {
                // The ray is entering this object, append it to the end of the list
                containing_objects_list.push_back(object_ptr);
                object_list_iterator_map[object_ptr] = std::prev(containing_objects_list.end());
            }

            if (intersection == hit && !containing_objects_list.empty()) {
                // The entered medium is an overlapping object
                const double n2{ containing_objects_list.back()->getMaterial().getRefractiveIndex() };

                // Terminate loop early since the correct entered object has been found
                return std::pair<double, double>{ n1, n2 };
            }
        }

        // All intersections have been checked, the entered medium is air
        return std::pair<double, double>{ n1, 1.0 };
    }
}