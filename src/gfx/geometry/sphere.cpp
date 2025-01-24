#include "sphere.hpp"

// Equality Operator
bool gfx::Sphere::operator==(const Sphere& rhs) const
{
    return m_transform == rhs.getTransform();
}