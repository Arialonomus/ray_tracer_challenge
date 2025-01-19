#include "vector.hpp"
#include "../utils/util_functions.hpp"

// Comparison Operator
bool gfx::Vector::operator==(const Vector& rhs) const
{
    return utils::areEqual(m_x, rhs.x())
        && utils::areEqual(m_y, rhs.y())
        && utils::areEqual(m_z, rhs.z())
        && utils::areEqual(m_w, rhs.w());
}

gfx::Vector gfx::operator+(const Vector& lhs, const Vector& rhs)
{
    return gfx::Vector{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
};