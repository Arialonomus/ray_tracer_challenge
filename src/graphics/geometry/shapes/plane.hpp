#pragma once

#include <limits>

#include "surface.hpp"

namespace gfx {
    class Plane : public Surface
    {
    public:
        /* Constructors */

        Plane() = default;
        explicit Plane(const Matrix4& transform)
                : Surface{ transform }
        {}
        explicit Plane(const Material& material)
        : Surface{ material }
        {}
        Plane(const Matrix4& transform, const Material& material)
                : Surface{ transform, material }
        {}
        Plane(const Plane&) = default;

        /* Destructor */

        ~Plane() override = default;

        /* Assignment Operators */

        Plane& operator=(const Plane&) = default;

        /* Accessors */

        [[nodiscard]] BoundingBox getBounds() const override
        { return BoundingBox{ -std::numeric_limits<double>::infinity(), 0, -std::numeric_limits<double>::infinity(),
                              std::numeric_limits<double>::infinity(), 0, std::numeric_limits<double>::infinity() }; }

        /* Object Operations */

        // Creates a clone of this plane to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Plane>(*this); }

    private:
        /* Shape Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;

        /* Object Helper Method Overrides */

        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;
    };
}
