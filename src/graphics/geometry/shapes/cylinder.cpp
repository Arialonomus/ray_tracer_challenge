#include "cylinder.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Cylinder::operator==(const Cylinder& rhs) const
    {
        return this->getTransform() == rhs.getTransform() && this->getMaterial() == rhs.getMaterial();
    }

    // Surface Normal for a Cylinder
    Vector4 Cylinder::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return createVector(transformed_point.x(), 0, transformed_point.z());
    }

    // Ray-Cylinder Intersection Calculator
    std::vector<Intersection> Cylinder::calculateIntersections(const Ray& transformed_ray) const
    {
        const Vector4 direction{ transformed_ray.getDirection() };
        const Vector4 origin{ transformed_ray.getOrigin() };

        const double a{ std::pow(direction.x(), 2) + std::pow(direction.z(), 2) };
        if (utils::areEqual(a, 0.0)) {
            // Ray is parallel to the y-axis
            return std::vector<Intersection>{ };
        }

        const double b{ (2 * origin.x() * direction.x()) + (2 * origin.z() * direction.z()) };
        const double c{ std::pow(origin.x(), 2) + std::pow(origin.z(), 2) - 1 };

        const double discriminant{ std::pow(b, 2) - (4 * a * c) };
        if (utils::isLess(discriminant, 0.0)) {
            // Ray misses the cylinder
            return std::vector<Intersection>{ };
        }

        // Calculate the intersection points for an unbounded cylinder
        double t_0{ (-b - std::sqrt(discriminant)) / (2 * a) };
        double t_1{ (-b + std::sqrt(discriminant)) / (2 * a) };
        if (utils::isGreater(t_0, t_1)) {
            std::swap(t_0, t_1);
        }

        // Check that intersection points land within cylinder bounds (if applicable)
        std::vector<Intersection> intersections{ };

        const double y_0{ transformed_ray.getOrigin().y() + t_0 * transformed_ray.getDirection().y() };
        if (utils::isLess(this->m_y_min, y_0) && utils::isLess(y_0, this->m_y_max)) {
            intersections.emplace_back( t_0, this );
        }
        const double y_1{ transformed_ray.getOrigin().y() + t_1 * transformed_ray.getDirection().y() };
        if (utils::isLess(this->m_y_min, y_1) && utils::isLess(y_1, this->m_y_max)) {
            intersections.emplace_back( t_1, this );
        }

        return intersections;
    }
}