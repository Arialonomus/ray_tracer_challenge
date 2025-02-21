#pragma once

#include "shape.hpp"

namespace gfx {
    class Cube : public Shape
    {
    public:
        /* Constructors */

        Cube() = default;
        explicit Cube(const Matrix4& transform)
                : Shape{ transform }
        {}
        explicit Cube(const Material& material)
                : Shape{ material }
        {}
        Cube(const Matrix4& transform, const Material& material)
                : Shape{ transform, material }
        {}
        Cube(const Cube&) = default;

        /* Destructor */

        ~Cube() override = default;

        /* Assignment Operators */

        Cube& operator=(const Cube&) = default;

        /* Accessors */

        [[nodiscard]] BoundingBox getBounds() const override
        { return BoundingBox{ -1, -1, -1,
                              1, 1, 1 }; }

        /* Object Operations */

        // Creates a clone of this cube to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Cube>(*this); }

    private:
        /* Shape Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;

        /* Object Helper Method Overrides */

        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;
    };
}
