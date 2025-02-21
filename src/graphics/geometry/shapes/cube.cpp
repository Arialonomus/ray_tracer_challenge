#include "cube.hpp"

#include <cmath>

#include "intersection.hpp"
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
        const auto [ t_min, t_max ] { calculateBoxIntersectionTs(transformed_ray,
                                                                 createPoint(-1, -1, -1),
                                                                 createPoint(1, 1, 1)) };

        if (utils::isGreater(t_min, t_max)) {
            return std::vector<Intersection>{ };
        } else {
            return std::vector<Intersection>{ Intersection{ t_min, this }, Intersection{ t_max, this } };
        }
    }

    // Cube Object Equivalency Check
    bool Cube::areEquivalent(const Object& other_object) const
    {
        const Cube& other_cube{ dynamic_cast<const Cube&>(other_object) };

        return
                this->getTransform() == other_cube.getTransform() &&
                this->getMaterial() == other_cube.getMaterial();
    }
}