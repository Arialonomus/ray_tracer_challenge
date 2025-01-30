#include "ray.hpp"

namespace gfx {
    // Equality Operator
    bool Ray::operator==(const Ray& rhs) const
    {
        return
                m_origin == rhs.getOrigin() &&
                m_direction == rhs.getDirection();
    }

    // Transform Ray
    Ray Ray::transform(const Matrix4& transform_matrix) const
    {
        return Ray{ transform_matrix * m_origin,
                    transform_matrix * m_direction };
    }
}