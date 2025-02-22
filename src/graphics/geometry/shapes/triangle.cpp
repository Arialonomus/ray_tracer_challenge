#include "triangle.hpp"

#include <cmath>

#include "intersection.hpp"
#include "util_functions.hpp"

namespace gfx {
    // Surface Normal for a Triangle
    Vector4 Triangle::calculateSurfaceNormal(const Vector4& transformed_point) const
    {
        return m_surface_normal;
    }

    // Ray-Triangle Intersection Calculator
    std::vector<Intersection> Triangle::calculateIntersections(const Ray& transformed_ray) const
    {
        return std::vector<Intersection>{ };
    }

    // Triangle Object Equivalency Check
    bool Triangle::areEquivalent(const Object& other_object) const
    {
        const Triangle& other_triangle{ dynamic_cast<const Triangle&>(other_object) };

        return

                this->getTransform() == other_triangle.getTransform() &&
                this->getMaterial() == other_triangle.getMaterial() &&
                this->getVertexA() == other_triangle.getVertexA() &&
                this->getVertexB() == other_triangle.getVertexB() &&
                this->getVertexC() == other_triangle.getVertexC();
    }

    void Triangle::preComputeTriangleData()
    {
        m_edge_a = m_vertex_b - m_vertex_a;
        m_edge_b = m_vertex_c - m_vertex_a;
        m_surface_normal = normalize(m_edge_b.crossProduct(m_edge_a));
        BoundingBox triangle_bounds{ };
        triangle_bounds.addPoint(m_vertex_a);
        triangle_bounds.addPoint(m_vertex_b);
        triangle_bounds.addPoint(m_vertex_c);
        m_bounds = triangle_bounds;
    }
}