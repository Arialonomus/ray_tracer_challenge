#include "camera.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    bool Camera::operator==(const Camera& rhs) const
    {
        return
            m_viewport_width == rhs.getViewportWidth() &&
            m_viewport_height == rhs.getViewportHeight() &&
            utils::areEqual(m_field_of_view, rhs.getFieldOfView()) &&
            m_transform == rhs.getTransform();
    }

    /* Private Methods */

    void Camera::updateCachedState()
    {
        const float half_view{ std::tanf(m_field_of_view / 2) };
        const float aspect_ratio{ static_cast<float>(m_viewport_width) / static_cast<float>(m_viewport_height) };

        // Viewport has horizontal aspect
        if (aspect_ratio >= 1) {
            m_half_width = half_view;
            m_half_height = half_view / aspect_ratio;
        }
        // Viewport has vertical aspect
        else {
            m_half_width = half_view * aspect_ratio;
            m_half_height = half_view;
        }

        // We assume a square pixel, so we only need to calculate one dimension
        m_pixel_size = (m_half_width * 2) / m_viewport_width;
    }
}