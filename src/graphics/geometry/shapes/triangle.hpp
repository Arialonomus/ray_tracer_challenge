#pragma once

#include "surface.hpp"

#include <vector>

namespace gfx {
    class Triangle : public Surface
    {
    public:
        /* Constructors */

        // Default Constructor
        Triangle() = delete;

        // Standard Constructor
        Triangle(const Vector4& vertex_a, const Vector4& vertex_b, const Vector4& vertex_c)
                : Surface{ },
                  m_vertex_a{ vertex_a },
                  m_vertex_b{ vertex_b },
                  m_vertex_c{ vertex_c },
                  m_edge_a{ },
                  m_edge_b{ },
                  m_surface_normal{ },
                  m_bounds{ }
        { preComputeTriangleData(); }

        // Copy Constructor
        Triangle(const Triangle&) = default;

        /* Destructor */

        ~Triangle() override = default;

        /* Assignment Operators */

        Triangle& operator=(const Triangle&) = default;

        /* Accessors */

        [[nodiscard]] const Vector4& getVertexA() const
        { return m_vertex_a; }

        [[nodiscard]] const Vector4& getVertexB() const
        { return m_vertex_b; }

        [[nodiscard]] const Vector4& getVertexC() const
        { return m_vertex_c; }

        [[nodiscard]] const Vector4& getEdgeA() const
        { return m_edge_a; }

        [[nodiscard]] const Vector4& getEdgeB() const
        { return m_edge_b; }

        [[nodiscard]] BoundingBox getBounds() const override
        { return m_bounds; }

        /* Object Operations */

        // Creates a clone of this sphere to be stored in an object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Triangle>(*this); }

    private:
        /* Data Members */
        Vector4 m_vertex_a{ };
        Vector4 m_vertex_b{ };
        Vector4 m_vertex_c{ };
        Vector4 m_edge_a{ };
        Vector4 m_edge_b{ };
        Vector4 m_surface_normal{ };
        BoundingBox m_bounds{ };

        /* Shape Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;

        /* Object Helper Method Overrides */

        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;

        /* Triangle Helper Methods */

        // Pre-computes the edges and normal vector to be stored on object construction
        void preComputeTriangleData();
    };
}
