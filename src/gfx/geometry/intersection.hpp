#pragma once

#include <vector>

#include "sphere.hpp"

namespace gfx {
    class Intersection
    {
    public:
        /* Constructors */

        Intersection() = delete;
        Intersection(const float t, const Sphere& object)
        : m_t{ t }, m_object{ object }
        {}
        Intersection(const Intersection&) = default;
        Intersection(Intersection&&) = default;

        /* Destructor */

        ~Intersection() = default;

        /* Assignment Operators */

        Intersection& operator=(const Intersection&) = default;
        Intersection& operator=(Intersection&&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator<(const Intersection& rhs) const
        { return m_t < rhs.getT(); }

        /* Accessors */

        [[nodiscard]] const float getT() const
        { return m_t; }
        [[nodiscard]] const Sphere& getObject() const
        { return m_object; }

    private:
        float m_t;
        std::reference_wrapper<const Sphere> m_object;
    };
}
