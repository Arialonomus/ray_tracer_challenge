#include "camera.hpp"

#include <cmath>

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

    // Pixel Size Accessor
    float Camera::getPixelSize() const
    {
        const float half_view{ std::tanf(m_field_of_view / 2) };
        const float aspect_ratio{ static_cast<float>(m_viewport_width) / static_cast<float>(m_viewport_height) };
        float half_width{ }, half_height{ };
        if (aspect_ratio >= 1) {
            half_width = half_view;
            half_height = half_view / aspect_ratio;
        } else {
            half_width = half_view * aspect_ratio;
            half_height = half_view;
        }

        return (half_width * 2) / m_viewport_width;
    }
}