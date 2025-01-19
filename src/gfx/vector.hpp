#pragma once

namespace gfx {
    class Vector
    {
    public:
        // Constructors
        Vector() = default;
        Vector(const float x, const float y, const float z) : m_x{ x }, m_y{ y }, m_z{ z } {}
        Vector(Vector&) = default;

        // Destructor
        ~Vector() = default;

        // Accessors
        [[nodiscard]] float x() const { return m_x; }
        [[nodiscard]] float y() const { return m_y; }
        [[nodiscard]] float z() const { return m_z; }
        [[nodiscard]] float w() const { return m_w; }

        // Operations
        [[nodiscard]] bool operator==(const Vector& rhs) const;

    private:
        float m_x{ 0.0 };
        float m_y{ 0.0 };
        float m_z{ 0.0 };
        float m_w{ 0.0 };
    };
}