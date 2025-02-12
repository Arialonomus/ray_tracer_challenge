#include "cube.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Cube::operator==(const Cube& rhs) const
    {
        return this->getTransform() == rhs.getTransform() && this->getMaterial() == rhs.getMaterial();
    }

    // Surface Normal for a Cube
    Vector4 Cube::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ };
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

        const double t_min{ std::max({ x_t_min, y_t_min, z_t_min }) };
        const double t_max{ std::min({ x_t_max, y_t_max, z_t_max }) };

        return std::vector<Intersection>{ Intersection{ t_min, this }, Intersection{ t_max, this } };
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