#include "cylinder.hpp"

#include <cmath>
#include <algorithm>

#include "intersection.hpp"
#include "util_functions.hpp"

namespace gfx {
    // Surface Normal for a Cylinder
    Vector4 Cylinder::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        const double y_axis_distance{ std::pow(transformed_point.x(), 2) + std::pow(transformed_point.z(), 2) };

        if (utils::isLess(y_axis_distance, 1.0) && utils::areEqual(transformed_point.y(), m_y_min)) {
            // Normal is on lower end cap
            return createVector(0, -1, 0);
        }

        if (utils::isLess(y_axis_distance, 1.0) && utils::areEqual(transformed_point.y(), m_y_max)) {
            // Normal is on upper end cap
            return createVector(0, 1, 0);
        }

        // Normal is on cylinder wall
        return createVector(transformed_point.x(), 0, transformed_point.z());
    }

    // Ray-Cylinder Intersection Calculator
    std::vector<Intersection> Cylinder::calculateIntersections(const Ray& transformed_ray) const
    {
        const Vector4 direction{ transformed_ray.getDirection() };
        const Vector4 origin{ transformed_ray.getOrigin() };
        std::vector<Intersection> intersections{ };

        const double a{ std::pow(direction.x(), 2) + std::pow(direction.z(), 2) };

        if (utils::areNotEqual(a, 0.0)) {
            // Ray is not parallel to y-axis, calculate cylinder wall intersection(s)
            const double b{ (2 * origin.x() * direction.x()) + (2 * origin.z() * direction.z()) };
            const double c{ std::pow(origin.x(), 2) + std::pow(origin.z(), 2) - 1 };
            const double discriminant{ std::pow(b, 2) - (4 * a * c) };
            if (utils::isLess(discriminant, 0.0)) {
                // Ray misses the cylinder
                return intersections;
            }

            // Calculate the intersection points for an unbounded cylinder
            double t_0{ (-b - std::sqrt(discriminant)) / (2 * a) };
            double t_1{ (-b + std::sqrt(discriminant)) / (2 * a) };
            if (utils::isGreater(t_0, t_1)) {
                std::swap(t_0, t_1);
            }

            // Check that intersection points land within cylinder bounds
            const double y_0{ transformed_ray.getOrigin().y() + t_0 * transformed_ray.getDirection().y() };
            if (utils::isLess(this->m_y_min, y_0) && utils::isLess(y_0, this->m_y_max)) {
                intersections.emplace_back(t_0, this);
            }
            const double y_1{ transformed_ray.getOrigin().y() + t_1 * transformed_ray.getDirection().y() };
            if (utils::isLess(this->m_y_min, y_1) && utils::isLess(y_1, this->m_y_max)) {
                intersections.emplace_back(t_1, this);
            }
        }

        // Calculate intersections for cylinder end caps (if any)
        intersections.append_range(calculateEndCapIntersections(transformed_ray));

        // Sort intersections and return
        std::sort(intersections.begin(), intersections.end());
        return intersections;
    }

    // Cylinder Object Equivalency Check
    bool Cylinder::areEquivalent(const Object& other_object) const
    {
        const Cylinder& other_cylinder{ dynamic_cast<const Cylinder&>(other_object) };

        return
                this->getTransform() == other_cylinder.getTransform() &&
                this->getMaterial() == other_cylinder.getMaterial() &&
                utils::areEqual(m_y_min, other_cylinder.getYMin()) &&
                utils::areEqual(m_y_max, other_cylinder.getYMax()) &&
                m_is_closed == other_cylinder.isClosed();
    }

    // End Cap Intersection Calculator
    std::vector<Intersection> Cylinder::calculateEndCapIntersections(const Ray& transformed_ray) const
    {
        const double ray_direction_y_val{ transformed_ray.getDirection().y() };
        if (!this->isClosed() || utils::areEqual(ray_direction_y_val, 0.0)) {
            // Intersections only possible if the cylinder is capped and could potentially be intersected by the ray
            return std::vector<Intersection>{ };
        }

        std::vector<Intersection> intersections{ };

        // Check for an intersection with the plane at the lower bound
        const double ray_origin_y_val{ transformed_ray.getOrigin().y() };
        const double t_lower{ (this->m_y_min - ray_origin_y_val) / ray_direction_y_val };
        if (isWithinCylinderWalls(transformed_ray, t_lower)) {
            intersections.emplace_back(t_lower, this);
        }

        // Check for an intersection with the plane at the upper bound
        const double t_upper{ (this->m_y_max - ray_origin_y_val) / ray_direction_y_val };
        if (isWithinCylinderWalls(transformed_ray, t_upper)) {
            intersections.emplace_back(t_upper, this);
        }

        return intersections;
    }


    // Check Point is Within Cylinder Boundaries
    bool Cylinder::isWithinCylinderWalls(const Ray& ray, double t)
    {
        const double x { ray.getOrigin().x() + t * ray.getDirection().x() };
        const double z { ray.getOrigin().z() + t * ray.getDirection().z() };

        return utils::isLessOrEqual(std::pow(x, 2) + std::pow(z, 2), 1.0);
    }
}