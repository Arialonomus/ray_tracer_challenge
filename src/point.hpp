#pragma once

class Point
{
public:
    // Constructors
    Point() = default;
    Point(float x, float y, float z);
    Point(Point&) = default;

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
