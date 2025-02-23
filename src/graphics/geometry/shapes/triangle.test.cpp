#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "triangle.hpp"

#include "matrix4.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the standard constructor
TEST(GraphicsTriangle, StandardConstructor)
{
    const gfx::Vector4 vertex_a_expected{ gfx::createPoint(0, 1, 0) };
    const gfx::Vector4 vertex_b_expected{ gfx::createPoint(-1, 0, 0) };
    const gfx::Vector4 vertex_c_expected{ gfx::createPoint(1, 0, 0) };
    const gfx::Triangle triangle{ vertex_a_expected,
                                  vertex_b_expected,
                                  vertex_c_expected };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    EXPECT_EQ(triangle.getTransform(), transform_expected);
    EXPECT_EQ(triangle.getMaterial(), material_expected);
    EXPECT_EQ(triangle.getVertexA(), vertex_a_expected);
    EXPECT_EQ(triangle.getVertexB(), vertex_b_expected);
    EXPECT_EQ(triangle.getVertexC(), vertex_c_expected);

    const gfx::Vector4 edge_a_expected{ gfx::createVector(-1, -1, 0) };
    const gfx::Vector4 edge_b_expected{ gfx::createVector(1, -1, 0) };
    EXPECT_EQ(triangle.getEdgeA(), edge_a_expected);
    EXPECT_EQ(triangle.getEdgeB(), edge_b_expected);
}

// Tests the copy constructor
TEST(GraphicsTriangle, CopyConstructor)
{
    const gfx::Vector4 vertex_a_expected{ gfx::createPoint(0, 1, 0) };
    const gfx::Vector4 vertex_b_expected{ gfx::createPoint(-1, 0, 0) };
    const gfx::Vector4 vertex_c_expected{ gfx::createPoint(1, 0, 0) };
    const gfx::Triangle triangle_src{ vertex_a_expected,
                                      vertex_b_expected,
                                      vertex_c_expected };
    const gfx::Triangle triangle_cpy{ triangle_src };

    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    EXPECT_EQ(triangle_cpy.getTransform(), transform_expected);
    EXPECT_EQ(triangle_cpy.getMaterial(), material_expected);
    EXPECT_EQ(triangle_cpy.getVertexA(), vertex_a_expected);
    EXPECT_EQ(triangle_cpy.getVertexB(), vertex_b_expected);
    EXPECT_EQ(triangle_cpy.getVertexC(), vertex_c_expected);

    const gfx::Vector4 edge_a_expected{ gfx::createVector(-1, -1, 0) };
    const gfx::Vector4 edge_b_expected{ gfx::createVector(1, -1, 0) };
    EXPECT_EQ(triangle_cpy.getEdgeA(), edge_a_expected);
    EXPECT_EQ(triangle_cpy.getEdgeB(), edge_b_expected);
}

// Tests the assignment operator
TEST(GraphicsTriangle, AssignmentOperator)
{
    const gfx::Vector4 vertex_a_expected{ gfx::createPoint(0, 1, 0) };
    const gfx::Vector4 vertex_b_expected{ gfx::createPoint(-1, 0, 0) };
    const gfx::Vector4 vertex_c_expected{ gfx::createPoint(1, 0, 0) };
    const gfx::Triangle triangle_a{ vertex_a_expected,
                                    vertex_b_expected,
                                    vertex_c_expected };
    gfx::Triangle triangle_b{ gfx::createPoint(0, 1, 0),
                              gfx::createPoint(0, 2, 0),
                              gfx::createPoint(0, 3, 0) };
    triangle_b = triangle_a;

    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    EXPECT_EQ(triangle_b.getTransform(), transform_expected);
    EXPECT_EQ(triangle_b.getMaterial(), material_expected);
    EXPECT_EQ(triangle_b.getVertexA(), vertex_a_expected);
    EXPECT_EQ(triangle_b.getVertexB(), vertex_b_expected);
    EXPECT_EQ(triangle_b.getVertexC(), vertex_c_expected);

    const gfx::Vector4 edge_a_expected{ gfx::createVector(-1, -1, 0) };
    const gfx::Vector4 edge_b_expected{ gfx::createVector(1, -1, 0) };
    EXPECT_EQ(triangle_b.getEdgeA(), edge_a_expected);
    EXPECT_EQ(triangle_b.getEdgeB(), edge_b_expected);
}

// Tests the equality operator
TEST(GraphicsTriangle, EqualityOperator)
{
    const gfx::Vector4 vertex_a{ gfx::createPoint(0, 1, 0) };
    const gfx::Vector4 vertex_b{ gfx::createPoint(-1, 0, 0) };
    const gfx::Vector4 vertex_c{ gfx::createPoint(1, 0, 0) };
    const gfx::Triangle triangle_a{ vertex_a,
                                    vertex_b,
                                    vertex_c };
    const gfx::Triangle triangle_b{ vertex_a,
                                    vertex_b,
                                    vertex_c };

    EXPECT_TRUE(triangle_a == triangle_b);
}

// Tests the inequality operator
TEST(GraphicsTriangle, InequalityOperator)
{
    const gfx::Vector4 vertex_a{ gfx::createPoint(0, 1, 0) };
    const gfx::Vector4 vertex_b{ gfx::createPoint(-1, 0, 0) };
    const gfx::Vector4 vertex_c{ gfx::createPoint(1, 0, 0) };
    const gfx::Triangle triangle_a{ vertex_a,
                                    vertex_b,
                                    vertex_c };
    const gfx::Triangle triangle_b{ gfx::createPoint(0, 1, 0),
                                    gfx::createPoint(0, 2, 0),
                                    gfx::createPoint(0, 3, 0) };

    EXPECT_TRUE(triangle_a != triangle_b);
}

// Tests getting the bounds of a triangle
TEST(GraphicsTriangle, GetBounds)
{
    const gfx::Triangle triangle{ gfx::createPoint(-3, 7, 2),
                                  gfx::createPoint(6, 2, -4),
                                  gfx::createPoint(2, -1, -1) };
    const gfx::BoundingBox triangle_bounds{ triangle.getBounds() };

    const gfx::Vector4 triangle_min_extent_expected{ gfx::createPoint(-3, -1, -4) };
    EXPECT_EQ(triangle_bounds.getMinExtentPoint(), triangle_min_extent_expected);

    const gfx::Vector4 triangle_max_extent_expected{ gfx::createPoint(6, 7, 2) };
    EXPECT_EQ(triangle_bounds.getMaxExtentPoint(), triangle_max_extent_expected);
}

// Test that the pre-computed normal on a triangle is used for every point
TEST(GraphicsTriangle, GetSurfaceNormal)
{
    const gfx::Triangle triangle{ gfx::createPoint(0, 1, 0),
                                  gfx::createPoint(-1, 0, 0),
                                  gfx::createPoint(1, 0, 0) };

    const gfx::Vector4 surface_normal_a{ triangle.getSurfaceNormalAt(gfx::createPoint(0, 0.5, 0)) };
    const gfx::Vector4 surface_normal_b{ triangle.getSurfaceNormalAt(gfx::createPoint(-0.5, 0.75, 0)) };
    const gfx::Vector4 surface_normal_c{ triangle.getSurfaceNormalAt(gfx::createPoint(0.5, 0.25, 0)) };

    EXPECT_TRUE(surface_normal_a == surface_normal_b && surface_normal_b == surface_normal_c);
}

// Test casting a ray parallel to a triangle
TEST(GraphicsTriangle, RayTriangleMissParallelRay)
{
    const gfx::Triangle triangle{ gfx::createPoint(0, 1, 0),
                                  gfx::createPoint(-1, 0, 0),
                                  gfx::createPoint(1, 0, 0) };

    const gfx::Ray ray{ 0, -1, -2,
                        0, 1, 0 };

    std::vector<gfx::Intersection> intersections{ triangle.getObjectIntersections(ray) };
    EXPECT_TRUE(intersections.empty());
}

// Test casting rays that miss each edge
TEST(GraphicsTriangle, RayTriangleMissEdges)
{
    const gfx::Triangle triangle{ gfx::createPoint(0, 1, 0),
                                  gfx::createPoint(-1, 0, 0),
                                  gfx::createPoint(1, 0, 0) };

    // Test a ray that misses Edge A (Vertex A to Vertex B)
    const gfx::Ray ray_a{ 0, -1, -2,
                          0, 1, 0 };

    std::vector<gfx::Intersection> intersections_a{ triangle.getObjectIntersections(ray_a) };
    EXPECT_TRUE(intersections_a.empty());

    // Test a ray that misses Edge B (Vertex A to Vertex C)
    const gfx::Ray ray_b{ 1, 1, -2,
                          0, 0, 1 };

    std::vector<gfx::Intersection> intersections_b{ triangle.getObjectIntersections(ray_b) };
    EXPECT_TRUE(intersections_b.empty());

    // Test a ray that misses Edge C (Vertex B to Vertex C)
    const gfx::Ray ray_c{ -1, 1, -2,
                          0, 0, 1 };

    std::vector<gfx::Intersection> intersections_c{ triangle.getObjectIntersections(ray_c) };
    EXPECT_TRUE(intersections_c.empty());
}

// Tests casting a ray that hits a triangle
TEST(GraphicsTriangle, RayTriangleHit)
{
    const gfx::Triangle triangle{ gfx::createPoint(0, 1, 0),
                                  gfx::createPoint(-1, 0, 0),
                                  gfx::createPoint(1, 0, 0) };

    const gfx::Ray ray{ 0, 0.5, -2,
                        0, 0, 1 };

    std::vector<gfx::Intersection> intersections{ triangle.getObjectIntersections(ray) };
    ASSERT_EQ(intersections.size(), 1);
    EXPECT_FLOAT_EQ(intersections.at(0).getT(), 2);
}

#pragma clang diagnostic pop