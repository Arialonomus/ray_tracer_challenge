#include "camera.hpp"

#include <cmath>

#include "util_functions.hpp"
#include "vector4.hpp"

namespace rt {
    bool Camera::operator==(const Camera& rhs) const
    {
        return
            m_viewport_width == rhs.getViewportWidth() &&
            m_viewport_height == rhs.getViewportHeight() &&
            utils::areEqual(m_field_of_view, rhs.getFieldOfView()) &&
            m_transform == rhs.getTransform();
    }

    const gfx::Ray Camera::castRay(const size_t pixel_x, const size_t pixel_y) const
    {
        // Calculate the offset from the edge of the viewport to the pixel's center
        const double pixel_x_offset{ (static_cast<double>(pixel_x) + 0.5f) * m_pixel_size };
        const double pixel_y_offset{ (static_cast<double>(pixel_y) + 0.5f) * m_pixel_size };

        // Calculate the un-transformed world-space coordinates of the pixel
        const double world_x{ m_half_width - pixel_x_offset };
        const double world_y{ m_half_height - pixel_y_offset };

        // Move the viewport pixel position and the world origin into camera space
        const gfx::Matrix4 inverse_transform{ m_transform.inverse() };
        const gfx::Vector4 pixel_camera_space_pos{
            inverse_transform * gfx::createPoint(world_x, world_y, -1) // Viewport is always 1 unit away from camera origin
        };
        const gfx::Vector4 origin_camera_space_pos{ inverse_transform * gfx::createPoint(0, 0 , 0) };

        // Calculate the ray direction and return the cast ray
        const gfx::Vector4 ray_cast_direction{ normalize(pixel_camera_space_pos - origin_camera_space_pos) };
        return gfx::Ray{ origin_camera_space_pos, ray_cast_direction };
    }

    /* Private Methods */

    void Camera::updateCachedState()
    {
        const double half_view{ std::tanf(m_field_of_view / 2) };
        const double aspect_ratio{ static_cast<double>(m_viewport_width) / static_cast<double>(m_viewport_height) };

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