#pragma once

#include <vector>

#include "vector4.hpp"
#include "matrix4.hpp"

namespace gfx {
    class Ray
    {
    public:
        /* Constructors */

        Ray() = default;
        Ray(const Vector4& origin, const Vector4& direction)
                : m_origin{ origin }, m_direction{ direction }
        {}
        Ray(const double origin_x, const double origin_y, const double origin_z,
            const double direction_x, const double direction_y, const double direction_z)
                : m_origin{ origin_x, origin_y, origin_z, 1.0 },
                  m_direction{ direction_x, direction_y, direction_z, 0.0 }
        {}
        Ray(const Ray&) = default;

        /* Destructor */

        ~Ray() = default;

        /* Assignment Operators */

        Ray& operator=(const Ray&) = default;

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
        [[nodiscard]] Vector4 position(const double t) const
        { return m_origin + (m_direction * t); }

        /* Ray-Tracing Operations */

        // Returns a ray transformed by multiplying it with a passed-in transformation matrix
        [[nodiscard]] Ray transform(const Matrix4& transform_matrix) const;

    private:
        /* Data Members */
        Vector4 m_origin{ 0.0, 0.0, 0.0, 1.0 };
        Vector4 m_direction{ 0.0, 0.0, 0.0, 0.0 };
    };
}
