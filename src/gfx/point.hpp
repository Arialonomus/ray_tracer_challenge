#pragma once

namespace gfx
{
    class Vector;   // Forward declaration for vector-point operations

    class Point
    {
    public:
        /* Constructors */

        Point() = default;
        Point(const float x, const float y, const float z) : m_x{ x }, m_y{ y }, m_z{ z } {}
        Point(const float x, const float y, const float z, const float w) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ w } {}
        Point(const Point&) = default;
        Point(Point&&) = default;

        /* Destructor */

        ~Point() = default;

        /* Assignment Operators */

        Point& operator=(const Point&) = default;
        Point& operator=(Point&&) = default;

        /* Accessors */

        [[nodiscard]] float x() const { return m_x; }
        [[nodiscard]] float y() const { return m_y; }
        [[nodiscard]] float z() const { return m_z; }
        [[nodiscard]] float w() const { return m_w; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Point& rhs) const;

        /* Arithmetic Operator Overloads */


        [[nodiscard]] Point operator-(const Vector& vec) const;
        Point& operator+=(const Vector& vec);
        Point& operator-=(const Vector& vec);


    private:
        float m_x{ 0.0 };
        float m_y{ 0.0 };
        float m_z{ 0.0 };
        float m_w{ 1.0 };
    };

    /* Global Arithmetic Operator Overloads */

    [[nodiscard]] Point operator+(const Point& lhs, const Vector& rhs);
    [[nodiscard]] Point operator+(const Vector& lhs, const Point& rhs);
}