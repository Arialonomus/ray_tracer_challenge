#include "cube.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    // Surface Normal for a Cube
    Vector4 Cube::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        const double abs_x{ std::abs(transformed_point.x()) };
        const double abs_y{ std::abs(transformed_point.y()) };
        const double abs_z{ std::abs(transformed_point.z()) };

        double max_component{ std::fmax(abs_x, abs_y) };
        max_component = std::fmax(max_component, abs_z);

        // X-Axis Aligned Face
        if (utils::areEqual(max_component, abs_x)) {
            return createVector(transformed_point.x(), 0, 0);
        }
        // Y-Axis Aligned Face
        if (utils::areEqual(max_component, abs_y)) {
            return createVector(0, transformed_point.y(), 0);
        }
        // Z-Axis Aligned Face
        return createVector(0, 0, transformed_point.z());
    }

    // Ray-Cube Intersection Calculator
    std::vector<Intersection> Cube::calculateIntersections(const Ray& transformed_ray) const
    {
        const auto [ x_t_min, x_t_max ] { getAxisIntersectionTs(transformed_ray.getOrigin().x(),
                                                                transformed_ray.getDirection().x()) };
        const auto [ y_t_min, y_t_max ] { getAxisIntersectionTs(transformed_ray.getOrigin().y(),
                                                                transformed_ray.getDirection().y()) };
        const auto [ z_t_min, z_t_max ] { getAxisIntersectionTs(transformed_ray.getOrigin().z(),
                                                                transformed_ray.getDirection().z()) };

        double t_min{ std::fmax( x_t_min, y_t_min ) };
        t_min = std::fmax(t_min, z_t_min);
        double t_max{ std::fmin( x_t_max, y_t_max ) };
        t_max = std::fmin(t_max, z_t_max);

        if (utils::isGreater(t_min, t_max)) {
            return std::vector<Intersection>{ };
        } else {
            return std::vector<Intersection>{ Intersection{ t_min, this }, Intersection{ t_max, this } };
        }
    }

    // Cube Object Equivalency Check
    bool Cube::areEquivalent(const Shape& other_shape) const
    {
        const Cube& other_cube{ dynamic_cast<const Cube&>(other_shape) };

        return
                this->getTransform() == other_cube.getTransform() &&
                this->getMaterial() == other_cube.getMaterial();
    }

    // Axis-Intersection Calculator
    std::pair<double, double> Cube::getAxisIntersectionTs(const double origin_axis_val,
                                                          const double direction_axis_val)
    {
        double t_min{ (-1 - origin_axis_val) / direction_axis_val };
        double t_max{ (1 - origin_axis_val) / direction_axis_val };

        if (utils::isGreater(t_min, t_max)) {
            std::swap(t_min, t_max);
        }

        return std::pair<double, double>{ t_min, t_max };
    }
}