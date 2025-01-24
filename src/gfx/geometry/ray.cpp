#include "ray.hpp"

// Equality Operator
bool gfx::Ray::operator==(const gfx::Ray& rhs) const
{
    return
        m_origin == rhs.getOrigin() &&
        m_direction == rhs.getDirection();
}
