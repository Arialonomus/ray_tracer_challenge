#pragma once

#include <vector>
#include <optional>

#include "sphere.hpp"
#include "ray.hpp"

namespace gfx {

    class Ray;  // Forward declaration

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

        virtual ~Intersection() = default;

        /* Assignment Operators */

        Intersection& operator=(const Intersection&) = default;
        Intersection& operator=(Intersection&&) = default;

        /* Accessors */

        [[nodiscard]] float getT() const
        { return m_t; }
        [[nodiscard]] const Sphere& getObject() const
        { return m_object; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Intersection& rhs) const;
        [[nodiscard]] bool operator<(const Intersection& rhs) const
        { return m_t < rhs.getT(); }
        [[nodiscard]] bool operator<(const float rhs) const
        { return m_t < rhs; }

    private:
        /* Data Members */

        float m_t;
        std::reference_wrapper<const Sphere> m_object;
    };

    // An extension of the intersection class containing pre-computed state information
    // about the intersection at that point
    class DetailedIntersection : public Intersection
    {
    public:
        /* Constructors */

        DetailedIntersection() = delete;
        DetailedIntersection(const Intersection& intersection, const Ray& ray);
        DetailedIntersection(const DetailedIntersection&) = default;
        DetailedIntersection(DetailedIntersection&&) = default;

        /* Destructor */

        ~DetailedIntersection() override = default;

        /* Assignment Operators */

        DetailedIntersection& operator=(const DetailedIntersection&) = default;
        DetailedIntersection& operator=(DetailedIntersection&&) = default;

        /* Accessors */

        [[nodiscard]] Vector4 getSurfacePosition() const
        { return m_surface_position; }
        [[nodiscard]] Vector4 getSurfaceNormal() const
        { return m_surface_normal; }
        [[nodiscard]] Vector4 getViewVector() const
        { return m_view_vector; }
        [[nodiscard]] Vector4 getOverPoint() const
        { return m_over_point; }
        [[nodiscard]] bool isInsideObject() const
        { return m_is_inside_object; }

    private:
        /* Data Members */

        Vector4 m_surface_position{ };
        Vector4 m_surface_normal{ };
        Vector4 m_view_vector{ };
        Vector4 m_over_point{ };
        bool m_is_inside_object{ false };
    };

    /* Global-Ray Tracing Operations */

    // Returns the first ray-object intersection with a non-negative t-value, representing a hit
    [[nodiscard]] std::optional<Intersection> getHit(std::vector<Intersection> intersections);
}
