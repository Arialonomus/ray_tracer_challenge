#include "camera.hpp"

#include "util_functions.hpp"

namespace gfx {
    // Equality Operator
    bool Camera::operator==(const Camera& rhs) const
    {
        return
            m_viewport_width == rhs.getViewportWidth() &&
            m_viewport_height == rhs.getViewportHeight() &&
            utils::areEqual(m_field_of_view, rhs.getFieldOfView()) &&
            m_transform == rhs.getTransform();
    }
}