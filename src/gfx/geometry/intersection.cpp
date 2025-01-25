#include "intersection.hpp"

#include <algorithm>

#include "util_functions.hpp"

namespace gfx {
    bool Intersection::operator==(const Intersection& rhs) const
    {
        return utils::areEqual(m_t, rhs.getT()) && m_object == rhs.getObject();
    }

    std::optional<Intersection> getHit(std::vector<Intersection> intersections)
    {
        std::sort(intersections.begin(), intersections.end());
        auto hit_iter = std::lower_bound(
                intersections.begin(),
                intersections.end(),
                0.0f);
        if (hit_iter != intersections.end()) {
            return *hit_iter;
        } else {
            return std::nullopt;
        }
    }
}