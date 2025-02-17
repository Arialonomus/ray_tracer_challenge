#include "cone.hpp"

#include <cmath>
#include <algorithm>

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Cone::operator==(const Cone& rhs) const
    {
        return
                this->getTransform() == rhs.getTransform() &&
                this->getMaterial() == rhs.getMaterial() &&
                utils::areEqual(m_y_min, rhs.getYMin()) &&
                utils::areEqual(m_y_max, rhs.getYMax()) &&
                m_is_closed == rhs.isClosed();
    }

    // Surface Normal for a Cone
    Vector4 Cone::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return Vector4{ };
    }

    // Ray-Cone Intersection Calculator
    std::vector<Intersection> Cone::calculateIntersections(const Ray& transformed_ray) const
    {
        return std::vector<Intersection>{ };
    }
}