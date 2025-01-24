#pragma once

#include "vector4.hpp"

namespace gfx {
    class Ray
    {
    public:
        /* Constructors */
        
        Ray() = default;
        Ray(const Vector4& origin, const Vector4& direction)
                : m_origin{ origin }, m_direction{ direction }
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
        [[nodiscard]] const Vector4 position(const float t) const
        { return m_origin + (m_direction * t); }

    private:
        Vector4 m_origin{ 0.0, 0.0, 0.0, 1.0 };
        Vector4 m_direction{ 0.0, 0.0, 0.0, 0.0 };
    };
}
