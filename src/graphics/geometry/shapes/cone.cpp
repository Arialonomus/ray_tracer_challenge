#include "cone.hpp"

#include <cmath>
#include <algorithm>

#include "util_functions.hpp"

namespace gfx {
    // Surface Normal for a Cone
    Vector4 Cone::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        const double y_axis_distance{ std::pow(transformed_point.x(), 2) + std::pow(transformed_point.z(), 2) };
        const double radius_at_point{ std::abs(transformed_point.y()) };

        if (utils::isLess(y_axis_distance, radius_at_point)) {
            if (utils::areEqual(transformed_point.y(), m_y_min)) {
                // Normal is on lower end cap
                return createVector(0, -1, 0);
            }

            if (utils::areEqual(transformed_point.y(), m_y_max)) {
                // Normal is on upper end cap
                return createVector(0, 1, 0);
            }
        }

        // Normal is on cone wall
        const double return_y_val{ std::sqrt(y_axis_distance) };
        return createVector(
                transformed_point.x(),
                utils::isGreater(transformed_point.y(), 0.0) ? -return_y_val : return_y_val,
                transformed_point.z()
                );
    }

    // Ray-Cone Intersection Calculator
    std::vector<Intersection> Cone::calculateIntersections(const Ray& transformed_ray) const
    {
        const Vector4 direction{ transformed_ray.getDirection() };
        const Vector4 origin{ transformed_ray.getOrigin() };

        const double a{ std::pow(direction.x(), 2) - std::pow(direction.y(), 2) + std::pow(direction.z(), 2) };
        const double b{ (2 * origin.x() * direction.x()) - (2 * origin.y() * direction.y()) + (2 * origin.z() * direction.z()) };
        const double c{ std::pow(origin.x(), 2) - std::pow(origin.y(), 2) + std::pow(origin.z(), 2) };

        std::vector<Intersection> intersections{ };

        // Check if ray  potentially intersects both cone halves
        if (utils::areNotEqual(a, 0.0)) {
            const double discriminant{ std::pow(b, 2) - (4 * a * c) };
            if (utils::isLess(discriminant, 0.0)) {
                // Ray misses the cone
                return intersections;
            }

            // Calculate the intersection points for an unbounded cone
            double t_0{ (-b - std::sqrt(discriminant)) / (2 * a) };
            double t_1{ (-b + std::sqrt(discriminant)) / (2 * a) };
            if (utils::isGreater(t_0, t_1)) {
                std::swap(t_0, t_1);
            }

            // Check that intersection points land within cone bounds (if applicable)
            const double y_0{ transformed_ray.getOrigin().y() + t_0 * transformed_ray.getDirection().y() };
            if (utils::isLess(this->m_y_min, y_0) && utils::isLess(y_0, this->m_y_max)) {
                intersections.emplace_back(t_0, this);
            }
            const double y_1{ transformed_ray.getOrigin().y() + t_1 * transformed_ray.getDirection().y() };
            if (utils::isLess(this->m_y_min, y_1) && utils::isLess(y_1, this->m_y_max)) {
                intersections.emplace_back(t_1, this);
            }
        }
        else if (utils::areNotEqual(b, 0.0)) {
            // Ray is parallel to one half of the cone, intersects the other
            intersections.emplace_back(-c / (2 * b), this);
        }

        // Calculate intersections for cone end caps (if applicable)
        intersections.append_range(calculateEndCapIntersections(transformed_ray));

        // Sort intersections and return
        std::sort(intersections.begin(), intersections.end());
        return intersections;
    }

    // Cone Object Equivalency Check
    bool Cone::areEquivalent(const Shape& other_shape) const
    {
        const Cone& other_cone{ dynamic_cast<const Cone&>(other_shape) };

        return
                this->getTransform() == other_cone.getTransform() &&
                this->getMaterial() == other_cone.getMaterial() &&
                utils::areEqual(m_y_min, other_cone.getYMin()) &&
                utils::areEqual(m_y_max, other_cone.getYMax()) &&
                m_is_closed == other_cone.isClosed();
    }

    // End Cap Intersection Calculator
    std::vector<Intersection> Cone::calculateEndCapIntersections(const Ray& transformed_ray) const
    {
        const double ray_direction_y_val{ transformed_ray.getDirection().y() };
        if (!this->isClosed() || utils::areEqual(ray_direction_y_val, 0.0)) {
            // Intersections only possible if the cone is capped and could potentially be intersected by the ray
            return std::vector<Intersection>{ };
        }

        std::vector<Intersection> intersections{ };

        // Check for an intersection with the plane at the lower bound
        const double ray_origin_y_val{ transformed_ray.getOrigin().y() };
        const double t_lower{ (this->m_y_min - ray_origin_y_val) / ray_direction_y_val };
        if (isWithinConeWalls(transformed_ray, t_lower, m_y_min)) {
            intersections.emplace_back(t_lower, this);
        }

        // Check for an intersection with the plane at the upper bound
        const double t_upper{ (this->m_y_max - ray_origin_y_val) / ray_direction_y_val };
        if (isWithinConeWalls(transformed_ray, t_upper, m_y_max)) {
            intersections.emplace_back(t_upper, this);
        }

        return intersections;
    }

    // Check Point is Within Cone Boundaries
    bool Cone::isWithinConeWalls(const Ray& ray, const double t, const double end_cap_y_val)
    {
        const double x { ray.getOrigin().x() + t * ray.getDirection().x() };
        const double z { ray.getOrigin().z() + t * ray.getDirection().z() };

        return utils::isLessOrEqual(std::pow(x, 2) + std::pow(z, 2), std::abs(end_cap_y_val));
    }
}