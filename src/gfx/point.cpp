#include "point.hpp"
#include "../utils/util_functions.hpp"


// Comparison Operator
bool gfx::Point::operator==(const Point& rhs) const
{
    return utils::areEqual(m_x, rhs.x())
        && utils::areEqual(m_y, rhs.y())
        && utils::areEqual(m_z, rhs.z())
        && utils::areEqual(m_w, rhs.w());
};
