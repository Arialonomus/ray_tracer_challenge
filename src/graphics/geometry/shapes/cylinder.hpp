#pragma once

#include "shape.hpp"

#include <vector>

#include "matrix4.hpp"
#include "vector4.hpp"
#include "material.hpp"
#include "intersection.hpp"
#include "ray.hpp"

namespace gfx {
    class Cylinder : public Shape
    {
    public:
        /* Constructors */

        Cylinder() = default;
        explicit Cylinder(const Matrix4& transform)
                : Shape{ transform }
        {}
        explicit Cylinder(const Material& material)
                : Shape{ material }
        {}
        Cylinder(const Matrix4& transform, const Material& material)
                : Shape{ transform, material }
        {}
        Cylinder(const Cylinder&) = default;

        /* Destructor */

        ~Cylinder() override = default;

        /* Assignment Operators */

        Cylinder& operator=(const Cylinder&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Cylinder& rhs) const;

        // Creates a clone of this cylinder to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Shape> clone() const override
        { return std::make_shared<Cylinder>(*this); }

    private:
        /* Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
    };
}
