#pragma once

#include "shape.hpp"

#include <vector>

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

        /* Object Operations */

        // Creates a clone of this sphere to be stored in an object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Sphere>(*this); }

    private:
        /* Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;
    };
}
