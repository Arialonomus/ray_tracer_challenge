#pragma once

#include <cstddef>

#include "matrix4.hpp"
#include "ray.hpp"

namespace rt {
    class Camera
    {
    public:
        /* Constructors */

        Camera() = delete;
        Camera(const size_t viewport_width,
               const size_t viewport_height,
               const float field_of_view)
                : m_viewport_width{ viewport_width },
                  m_viewport_height{ viewport_height },
                  m_field_of_view{ field_of_view },
                  m_transform{ gfx::createIdentityMatrix() },
                  m_pixel_size{},
                  m_half_width{},
                  m_half_height{}
        {
            updateCachedState();
        }
        Camera(const size_t viewport_width,
               const size_t viewport_height,
               const float field_of_view,
               const gfx::Matrix4& transform_matrix)
                : m_viewport_width{ viewport_width },
                  m_viewport_height{ viewport_height },
                  m_field_of_view{ field_of_view },
                  m_transform{ transform_matrix },
                  m_pixel_size{},
                  m_half_width{},
                  m_half_height{}
        {
            updateCachedState();
        }
        Camera(const Camera&) = default;
        Camera(Camera&&) = default;

        /* Destructor */

        ~Camera() = default;

        /* Assignment Operators */

        Camera& operator=(const Camera&) = default;
        Camera& operator=(Camera&&) = default;

        /* Accessors */

        [[nodiscard]] size_t getViewportWidth() const
        { return m_viewport_width; }

        [[nodiscard]] size_t getViewportHeight() const
        { return m_viewport_height; }

        [[nodiscard]] float getFieldOfView() const
        { return m_field_of_view; }

        [[nodiscard]] const gfx::Matrix4& getTransform() const
        { return m_transform; }

        /* Mutators */

        void setViewport(const size_t width, const size_t height)
        {
            m_viewport_width = width;
            m_viewport_height = height;
            updateCachedState();
        }

        void setViewportWidth(const size_t width)
        {
            m_viewport_width = width;
            updateCachedState();
        }

        void setViewportHeight(const size_t height)
        {
            m_viewport_height = height;
            updateCachedState();
        }

        void setFieldOfView(const float field_of_view)
        { m_field_of_view = field_of_view; }

        void setTransform(const gfx::Matrix4& transform_matrix)
        { m_transform = transform_matrix; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Camera& rhs) const;

        /* Ray Tracing Operations */

        // Returns a ray targeting a specific (x, y) coordinate in the viewport
        [[nodiscard]] const gfx::Ray castRay(size_t pixel_x, size_t pixel_y) const;

    private:
        /* Data Members */

        size_t m_viewport_width;
        size_t m_viewport_height;
        float m_field_of_view;
        gfx::Matrix4 m_transform;

        /* Cached State */
        // These variables are dependent on the viewport dimensions. However, because they are used in
        // castRay(), calculating them on-the-fly is impractical since castRay() can potentially be called
        // millions of times for large viewport resolutions. Therefore, we cache these values and
        // update them upon changes to the camera viewport.

        float m_pixel_size;
        float m_half_width;
        float m_half_height;

        /* Helper Methods */

        // Updates the cached state variables with the current viewport dimension values
        void updateCachedState();
    };
}
