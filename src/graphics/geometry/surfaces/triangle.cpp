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
        const Vector4 ray_direction{ transformed_ray.getDirection() };
        const Vector4 ray_cross_edge_b{ ray_direction.crossProduct(m_edge_b) };
        const double determinant{ dotProduct(m_edge_a, ray_cross_edge_b) } ;

        if (utils::areEqual(determinant, 0.0))
            // Ray is parallel to the triangle plane
            return std::vector<Intersection>{ };

        const Vector4 ray_origin{ transformed_ray.getOrigin() };
        const double inverse_determinant{ 1.0 / determinant };
        const Vector4 vertex_a_to_origin{ ray_origin - m_vertex_a };
        const double u { inverse_determinant * dotProduct(vertex_a_to_origin, ray_cross_edge_b) };

        if (utils::isLess(u, 0.0) || utils::isGreater(u, 1.0))
            // Ray misses Edge B (Vertex A to Vertex C)
            return std::vector<Intersection>{ };

        const Vector4 origin_cross_edge_a{ vertex_a_to_origin.crossProduct(m_edge_a) };
        const double v { inverse_determinant * dotProduct(ray_direction, origin_cross_edge_a) };

        if (utils::isLess(v, 0.0) || utils::isGreater(u + v, 1.0))
            // Ray misses Edges B & C
            return std::vector<Intersection>{ };

        // Ray intersects the triangle
        const double t { inverse_determinant * dotProduct(m_edge_b, origin_cross_edge_a) };
        return std::vector<Intersection>{ { t, this } };
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