#pragma once

#include "surface.hpp"

#include <vector>

namespace gfx {
    class Sphere : public Surface
    {
    public:
        /* Constructors */

        Sphere() = default;
        explicit Sphere(const Matrix4& transform)
                : Surface{ transform }
        {}
        explicit Sphere(const Material& material)
                : Surface{ material }
        {}
        Sphere(const Matrix4& transform, const Material& material)
                : Surface{ transform, material }
        {}
        Sphere(const Sphere&) = default;

        /* Destructor */

        ~Sphere() override = default;

        /* Assignment Operators */

        Sphere& operator=(const Sphere&) = default;

        /* Accessors */

        [[nodiscard]] BoundingBox getBounds() const override
        { return BoundingBox{ -1, -1, -1,
                              1, 1, 1 }; }

        /* Object Operations */

        // Creates a clone of this sphere to be stored in an object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Sphere>(*this); }

    private:
        /* Shape Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;

        /* Object Helper Method Overrides */

        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;
    };
}
