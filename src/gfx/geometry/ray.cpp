#include "ray.hpp"

namespace gfx {
    // Equality Operator
    bool Ray::operator==(const Ray& rhs) const
    {
        return
                m_origin == rhs.getOrigin() &&
                m_direction == rhs.getDirection();
    }
}