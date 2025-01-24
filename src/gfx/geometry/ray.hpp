#pragma once

#include <vector>

#include "vector4.hpp"
#include "sphere.hpp"

namespace gfx {
    class Ray
    {
    public:
        /* Constructors */

        Ray() = default;

        Ray(const Vector4& origin, const Vector4& direction)
                : m_origin{ origin }, m_direction{ direction }
        {}
        Ray(const float origin_x, const float origin_y, const float origin_z,
            const float direction_x, const float direction_y, const float direction_z)
                : m_origin{ origin_x, origin_y, origin_z, 1.0 },
                  m_direction{ direction_x, direction_y, direction_z, 0.0 }
        {}
        Ray(const Ray&) = default;
        Ray(const Ray&&) = default;

        /* Destructor */

        ~Ray() = default;

        /* Assignment Operators */

        Ray& operator=(const Ray&) = default;
        Ray& operator=(Ray&&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Ray& rhs) const;

        /* Accessors */

        // Returns the origin for this ray
        [[nodiscard]] const Vector4& getOrigin() const
        { return m_origin; }

        // Returns the direction for this ray
        [[nodiscard]] const Vector4& getDirection() const
        { return m_direction; }

        // Returns the position along the ray at a distance t from the origin
        [[nodiscard]] Vector4 position(const float t) const
        { return m_origin + (m_direction * t); }

        /* Ray-Tracing Operations */

        // Returns a vector of floats representing the t-values at which ray intersects a passed-in sphere
        [[nodiscard]] std::vector<float> getIntersections(const Sphere& sphere) const;

    private:
        Vector4 m_origin{ 0.0, 0.0, 0.0, 1.0 };
        Vector4 m_direction{ 0.0, 0.0, 0.0, 0.0 };
    };

    struct Intersection {
        float t;
        Sphere& object;
    };
}
