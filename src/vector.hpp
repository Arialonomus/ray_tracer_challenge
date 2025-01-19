#pragma once

namespace gfx {
    class Vector
    {
    public:
        // Constructors
        Vector() = default;
        Vector(float x, float y, float z);
        Vector(Vector&) = default;

        // Destructor
        ~Vector() = default;

        // Accessors
        float x() const { return m_x; }
        float y() const { return m_y; }
        float z() const { return m_z; }
        float w() const { return m_w; }

    private:
        float m_x{ 0.0 };
        float m_y{ 0.0 };
        float m_z{ 0.0 };
        float m_w{ 0.0 };
    };
}