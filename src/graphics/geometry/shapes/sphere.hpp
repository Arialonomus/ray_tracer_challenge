#pragma once

#include "shape.hpp"

#include <vector>

#include "matrix4.hpp"
#include "vector4.hpp"
#include "material.hpp"
#include "intersection.hpp"
#include "ray.hpp"

namespace gfx {
    class Sphere : public Shape
    {
    public:
        /* Constructors */

        Sphere() = default;
        explicit Sphere(const Matrix4& transform)
                : Shape{ transform }
        {}
        explicit Sphere(const Material& material)
                : Shape{ material }
        {}
        Sphere(const Matrix4& transform, const Material& material)
                : Shape{ transform, material }
        {}
        Sphere(const Sphere&) = default;

        /* Destructor */

        ~Sphere() override = default;

        /* Assignment Operators */

        Sphere& operator=(const Sphere&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Sphere& rhs) const;

        // Creates a clone of this sphere to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Shape> clone() const override
        { return std::make_shared<Sphere>(*this); }

    private:
        /* Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
    };
}
