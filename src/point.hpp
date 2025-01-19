#pragma once

namespace gfx
{
    class Point
    {
    public:
        // Constructors
        Point() = default;
        Point(const float x, const float y, const float z) : m_x{ x }, m_y{ y }, m_z{ z } {}
        Point(const Point&) = default;

        // Destructor
        ~Point() = default;

        // Accessors
        float x() const { return m_x; }
        float y() const { return m_y; }
        float z() const { return m_z; }
        float w() const { return m_w; }

    private:
        float m_x{ 0.0 };
        float m_y{ 0.0 };
        float m_z{ 0.0 };
        float m_w{ 1.0 };
    };
}