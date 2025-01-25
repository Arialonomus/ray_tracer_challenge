#include "intersection.hpp"

#include <algorithm>

#include "util_functions.hpp"

namespace gfx {
    bool Intersection::operator==(const Intersection& rhs) const
    {
        return utils::areEqual(m_t, rhs.getT()) && m_object == rhs.getObject();
    }
}