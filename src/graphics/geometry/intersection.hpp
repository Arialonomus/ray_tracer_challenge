#pragma once

#include <vector>
#include <optional>

#include "shape.hpp"
#include "ray.hpp"

namespace gfx {
    // Forward declarations
    class Shape;
    class Ray;

    class Intersection
    {
    public:
        /* Constructors */

        Intersection() = delete;

        Intersection(const double t, const Shape* object_ptr)
                : m_t{ t }, m_object_ptr{ object_ptr }
        {}

        Intersection(const Intersection&) = default;
        Intersection(Intersection&&) = default;

        /* Destructor */

        virtual ~Intersection() = default;

        /* Assignment Operators */

        Intersection& operator=(const Intersection&) = default;
        Intersection& operator=(Intersection&&) = default;

        /* Accessors */

        [[nodiscard]] double getT() const
        { return m_t; }

        [[nodiscard]] const Shape& getObject() const
        { return *m_object_ptr; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Intersection& rhs) const;

        [[nodiscard]] bool operator<(const Intersection& rhs) const
        { return m_t < rhs.getT(); }

        [[nodiscard]] bool operator<(const double rhs) const
        { return m_t < rhs; }

    private:
        /* Data Members */

        double m_t;
        const Shape* m_object_ptr;   // Shapes should always exist during the lifetime of the intersection
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

        [[nodiscard]] Vector4 getIntersectionPosition() const
        { return m_intersection_position; }

        [[nodiscard]] Vector4 getSurfaceNormal() const
        { return m_surface_normal; }

        [[nodiscard]] Vector4 getViewVector() const
        { return m_view_vector; }

        [[nodiscard]] Vector4 getReflectionVector() const
        { return m_reflection_vector; }

        [[nodiscard]] Vector4 getOverPoint() const
        { return m_over_point; }

        [[nodiscard]] Vector4 getUnderPoint() const
        { return m_under_point; }

        [[nodiscard]] bool isInsideObject() const
        { return m_is_inside_object; }

    private:
        /* Data Members */

        Vector4 m_intersection_position{ };
        Vector4 m_surface_normal{ };
        Vector4 m_view_vector{ };
        Vector4 m_reflection_vector{ };
        Vector4 m_over_point{ };
        Vector4 m_under_point{ };
        bool m_is_inside_object{ false };
    };

    /* Global Ray-Tracing Operations */

    // Returns the first ray-object intersection with a non-negative t-value, representing a hit
    [[nodiscard]] std::optional<Intersection> getHit(std::vector<Intersection> intersections);

    // Returns a pair representing T-values for ray intersections with an axis-aligned bounding box
    [[nodiscard]] std::pair<double, double> calculateBoxIntersectionTs(const Ray& ray,
                                                                       const Vector4& box_min_extent,
                                                                       const Vector4& box_max_extent);

    // Returns the t-values at which a given ray intersects an axis
    [[nodiscard]] std::pair<double, double> getAxisIntersectionTs(double origin_axis_val,
                                                                  double direction_axis_val,
                                                                  double min_extent_axis_val,
                                                                  double max_extent_axis_val);
}
