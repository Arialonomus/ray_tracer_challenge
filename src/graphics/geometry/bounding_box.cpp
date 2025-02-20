#include "bounding_box.hpp"

#include "util_functions.hpp"

namespace gfx {
    void BoundingBox::addPoint(const Vector4& point)
    {
        // X-Values
        if (utils::isLess(point.x(), m_min_extents[0]))
            m_min_extents[0] = point.x();
        if (utils::isGreater(point.x(), m_max_extents[0]))
            m_max_extents[0] = point.x();

        // Y-Values
        if (utils::isLess(point.y(), m_min_extents[1]))
            m_min_extents[1] = point.y();
        if (utils::isGreater(point.y(), m_max_extents[1]))
            m_max_extents[1] = point.y();

        // Z-Values
        if (utils::isLess(point.z(), m_min_extents[2]))
            m_min_extents[2] = point.z();
        if (utils::isGreater(point.z(), m_max_extents[2]))
            m_max_extents[2] = point.z();
    }
}