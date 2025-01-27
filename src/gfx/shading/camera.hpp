#pragma once

#include <cstddef>

#include "matrix4.hpp"

namespace gfx {
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
                  m_transform{ createIdentityMatrix() }
        {}
        Camera(const size_t viewport_width,
               const size_t viewport_height,
               const float field_of_view,
               const Matrix4& transform_matrix)
                : m_viewport_width{ viewport_width },
                m_viewport_height{ viewport_height },
                m_field_of_view{ field_of_view },
                m_transform{ transform_matrix }
        {}
        Camera(const Camera&) = default;
        Camera(Camera&&) = default;

        /* Destructor */

        ~Camera() = default;

        /* Assignment Operators */

        Camera& operator=(const Camera&) = default;
        Camera& operator=(Camera&&) = default;

        /* Accessors */

        [[nodiscard]] size_t getViewportWidth() const { return m_viewport_width; }
        [[nodiscard]] size_t getViewportHeight() const { return m_viewport_height; }
        [[nodiscard]] float getFieldOfView() const { return m_field_of_view; }
        [[nodiscard]] const Matrix4& getTransform() const { return m_transform; }

        // Returns the world-space size of pixels in the viewport
        [[nodiscard]] float getPixelSize() const;

        /* Mutators */

        void setViewport(const size_t width, const size_t height)
        {
            m_viewport_width = width;
            m_viewport_height = height;
        }
        void setViewportWidth(const size_t width) { m_viewport_width = width; }
        void setViewportHeight(const size_t height) { m_viewport_height = height; }
        void setFieldOfView(const float field_of_view) { m_field_of_view = field_of_view; }
        void setTransform(const Matrix4& transform_matrix) { m_transform = transform_matrix; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Camera& rhs) const;

    private:
        /* Data Members */

        size_t m_viewport_width;
        size_t m_viewport_height;
        float m_field_of_view;
        Matrix4 m_transform;
    };
}
