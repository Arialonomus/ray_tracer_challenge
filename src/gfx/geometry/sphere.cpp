#include "sphere.hpp"

namespace gfx {
// Equality Operator
    bool Sphere::operator==(const Sphere& rhs) const
    {
        return m_transform == rhs.getTransform();
    }
}