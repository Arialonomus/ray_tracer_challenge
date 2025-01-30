#pragma once

#include "shape.hpp"

namespace gfx {
    class Plane : public Shape
    {
    public:
        /* Constructors */

        Plane() = default;
        explicit Plane(const Matrix4& transform)
                : Shape{ transform }
        {}
        explicit Plane(const Material& material)
        : Shape{ material }
        {}
        Plane(const Matrix4& transform, const Material& material)
                : Shape{ transform, material }
        {}
        Plane(const Plane&) = default;

        /* Destructor */

        ~Plane() override = default;

        /* Assignment Operators */

        Plane& operator=(const Plane&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Plane& rhs) const;

        /* Object Operations */

        // Creates a clone of this plane to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Shape> clone() const override
        { return std::make_shared<Plane>(*this); }

    private:
        /* Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
    };
}
