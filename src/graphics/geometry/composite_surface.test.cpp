#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "composite_surface.hpp"

#include <cmath>
#include <vector>

#include "transform.hpp"
#include "sphere.hpp"
#include "cylinder.hpp"
#include "ray.hpp"
#include "intersection.hpp"

// Tests the default constructor
TEST(GraphicsCompositeSurface, DefaultConstructor)
{
    const gfx::CompositeSurface composite_surface{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    EXPECT_EQ(composite_surface.getTransform(), transform_expected);
    ASSERT_TRUE(composite_surface.isEmpty());
}

// Tests the transform-only constructor
TEST(GraphicsCompositeSurface, TransformOnlyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::CompositeSurface composite_surface{ transform_expected };

    EXPECT_EQ(composite_surface.getTransform(), transform_expected);
    ASSERT_TRUE(composite_surface.isEmpty());
}

// Tests the object list constructor
TEST(GraphicsCompositeSurface, ObjectListConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

    // Test building directly from objects
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::CompositeSurface composite_surface_a{ sphere_a, sphere_b };

    EXPECT_EQ(composite_surface_a.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_a.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_a.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_a.getChildAt(0).getParent(), &composite_surface_a);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_a.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_a.getChildAt(1).getParent(), &composite_surface_a);

    // Test building from object pointers
    const std::shared_ptr<gfx::Sphere> sphere_a_ptr{ std::make_shared<gfx::Sphere>(sphere_a) };
    const std::shared_ptr<gfx::Sphere> sphere_b_ptr{ std::make_shared<gfx::Sphere>(sphere_b) };

    const gfx::CompositeSurface composite_surface_b{ sphere_a_ptr, sphere_b_ptr };

    ASSERT_EQ(composite_surface_b.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_b.getChildAt(0).getParent(), &composite_surface_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_b.getChildAt(1).getParent(), &composite_surface_b);
}

// Tests the standard constructor
TEST(GraphicsCompositeSurface, StandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

    // Test building directly from objects
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::CompositeSurface composite_surface_a{ transform_expected, sphere_a, sphere_b };

    EXPECT_EQ(composite_surface_a.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_a.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_a.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_a.getChildAt(0).getParent(), &composite_surface_a);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_a.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_a.getChildAt(1).getParent(), &composite_surface_a);

    // Test building from object pointers
    const std::shared_ptr<gfx::Sphere> sphere_a_ptr{ std::make_shared<gfx::Sphere>(sphere_a) };
    const std::shared_ptr<gfx::Sphere> sphere_b_ptr{ std::make_shared<gfx::Sphere>(sphere_b) };

    const gfx::CompositeSurface composite_surface_b{ transform_expected, sphere_a_ptr, sphere_b_ptr };

    EXPECT_EQ(composite_surface_b.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_b.getChildAt(0).getParent(), &composite_surface_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_b.getChildAt(1).getParent(), &composite_surface_b);
}

// Tests the copy constructor
TEST(GraphicsCompositeSurface, CopyConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::CompositeSurface composite_surface_src{ transform_expected, sphere_a, sphere_b };
    const gfx::CompositeSurface composite_surface_cpy{ composite_surface_src };

    EXPECT_EQ(composite_surface_cpy.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_cpy.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_cpy.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_cpy.getChildAt(0).getParent(), &composite_surface_cpy);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_cpy.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_cpy.getChildAt(1).getParent(), &composite_surface_cpy);
}

// Tests the move constructor
TEST(GraphicsCompositeSurface, MoveConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    gfx::CompositeSurface composite_surface_src{ transform_expected, sphere_a, sphere_b };
    const gfx::CompositeSurface composite_surface_moved{ std::move(composite_surface_src) };

    EXPECT_EQ(composite_surface_moved.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_moved.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_moved.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_moved.getChildAt(0).getParent(), &composite_surface_moved);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_moved.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_moved.getChildAt(1).getParent(), &composite_surface_moved);
}

// Tests the assignment operator
TEST(GraphicsCompositeSurface, AssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::CompositeSurface composite_surface_a{ transform_expected, sphere_a, sphere_b };
    gfx::CompositeSurface composite_surface_b{ };

    composite_surface_b = composite_surface_a;

    EXPECT_EQ(composite_surface_b.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_b.getChildAt(0).getParent(), &composite_surface_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_b.getChildAt(1).getParent(), &composite_surface_b);
}

// Tests the move assignment operator
TEST(GraphicsCompositeSurface, MoveAssignmentOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    gfx::CompositeSurface composite_surface_a{ transform_expected, sphere_a, sphere_b };
    gfx::CompositeSurface composite_surface_b{ };

    composite_surface_b = std::move(composite_surface_a);

    EXPECT_EQ(composite_surface_b.getTransform(), transform_expected);
    ASSERT_FALSE(composite_surface_b.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface_b.getChildAt(0).getParent(), &composite_surface_b);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface_b.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface_b.getChildAt(1).getParent(), &composite_surface_b);
}

// Tests the equality operator
TEST(GraphicsCompositeSurface, EqualityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::CompositeSurface composite_surface_a{ transform_expected, sphere_a, sphere_b };
    gfx::CompositeSurface composite_surface_b{ composite_surface_a };

    EXPECT_TRUE(composite_surface_a == composite_surface_b);
}

// Tests the inequality operator
TEST(GraphicsCompositeSurface, InequalityOperator)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::CompositeSurface composite_surface_a{ transform_expected, sphere_a, sphere_b };
    const gfx::CompositeSurface composite_surface_b{ };

    EXPECT_TRUE(composite_surface_a != composite_surface_b);
}

// Tests adding children to the composite surface
TEST(GraphicsCompositeSurface, AddChild)
{
    gfx::CompositeSurface composite_surface{ };
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };

    // Add object directly
    composite_surface.addChild(sphere_a);

    // Add object via shared pointer
    composite_surface.addChild(std::make_shared<gfx::Sphere>(sphere_b));

    ASSERT_FALSE(composite_surface.isEmpty());
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface.getChildAt(0)), sphere_a);
    EXPECT_EQ(composite_surface.getChildAt(0).getParent(), &composite_surface);
    EXPECT_EQ(dynamic_cast<const gfx::Sphere&>(composite_surface.getChildAt(1)), sphere_b);
    EXPECT_EQ(composite_surface.getChildAt(1).getParent(), &composite_surface);
}

// Tests getting the bounds of a composite surface
TEST(GraphicsCompositeSurface, GetBounds)
{
    const std::shared_ptr<gfx::Sphere> sphere_ptr{ std::make_shared<gfx::Sphere>(
            gfx::createTranslationMatrix(2, 5, -3) * gfx::createScalingMatrix(2))
    };
    const std::shared_ptr<gfx::Cylinder> cylinder_ptr{ std::make_shared<gfx::Cylinder>(
            gfx::createTranslationMatrix(-4, -1, 4) * gfx::createScalingMatrix(0.5, 1, 0.5),
            -2,
            2)
    };

    // Test bounds calculations via object pointer list constructor
    const gfx::CompositeSurface composite_surface_a{ sphere_ptr, cylinder_ptr };
    const gfx::BoundingBox composite_surface_a_bounds{ composite_surface_a.getBounds() };

    const gfx::Vector4 composite_surface_a_min_extent_expected{ gfx::createPoint(-4.5, -3, -5) };
    const gfx::Vector4 composite_surface_a_min_extent_actual{ composite_surface_a_bounds.getMinExtentPoint() };
    EXPECT_EQ(composite_surface_a_min_extent_actual, composite_surface_a_min_extent_expected);

    const gfx::Vector4 composite_surface_a_max_extent_expected{ gfx::createPoint(4, 7, 4.5) };
    const gfx::Vector4 composite_surface_a_max_extent_actual{ composite_surface_a_bounds.getMaxExtentPoint() };
    EXPECT_EQ(composite_surface_a_max_extent_actual, composite_surface_a_max_extent_expected);

    // Test bounds calculations via adding object pointers individually
    gfx::CompositeSurface composite_surface_b{ };
    composite_surface_b.addChild(sphere_ptr);
    composite_surface_b.addChild(cylinder_ptr);
    const gfx::BoundingBox composite_surface_b_bounds{ composite_surface_b.getBounds() };

    const gfx::Vector4 composite_surface_b_min_extent_expected{ gfx::createPoint(-4.5, -3, -5) };
    const gfx::Vector4 composite_surface_b_min_extent_actual{ composite_surface_b_bounds.getMinExtentPoint() };
    EXPECT_EQ(composite_surface_b_min_extent_actual, composite_surface_b_min_extent_expected);

    const gfx::Vector4 composite_surface_b_max_extent_expected{ gfx::createPoint(4, 7, 4.5) };
    const gfx::Vector4 composite_surface_b_max_extent_actual{ composite_surface_b_bounds.getMaxExtentPoint() };
    EXPECT_EQ(composite_surface_b_max_extent_actual, composite_surface_b_max_extent_expected);

    // Test bounds calculations via object list constructor
    const gfx::Sphere sphere{ gfx::createTranslationMatrix(2, 5, -3) * gfx::createScalingMatrix(2) };
    const gfx::Cylinder cylinder{ gfx::createTranslationMatrix(-4, -1, 4) * gfx::createScalingMatrix(0.5, 1, 0.5),
                                  -2,
                                  2 };

    const gfx::CompositeSurface composite_surface_c{ sphere, cylinder };
    const gfx::BoundingBox composite_surface_c_bounds{ composite_surface_c.getBounds() };

    const gfx::Vector4 composite_surface_c_min_extent_expected{ gfx::createPoint(-4.5, -3, -5) };
    const gfx::Vector4 composite_surface_c_min_extent_actual{ composite_surface_c_bounds.getMinExtentPoint() };
    EXPECT_EQ(composite_surface_c_min_extent_actual, composite_surface_c_min_extent_expected);

    const gfx::Vector4 composite_surface_c_max_extent_expected{ gfx::createPoint(4, 7, 4.5) };
    const gfx::Vector4 composite_surface_c_max_extent_actual{ composite_surface_c_bounds.getMaxExtentPoint() };
    EXPECT_EQ(composite_surface_c_max_extent_actual, composite_surface_c_max_extent_expected);

    // Test bounds calculations via adding object pointers individually
    gfx::CompositeSurface composite_surface_d{ };
    composite_surface_d.addChild(sphere);
    composite_surface_d.addChild(cylinder);
    const gfx::BoundingBox composite_surface_d_bounds{ composite_surface_d.getBounds() };

    const gfx::Vector4 composite_surface_d_min_extent_expected{ gfx::createPoint(-4.5, -3, -5) };
    const gfx::Vector4 composite_surface_d_min_extent_actual{ composite_surface_d_bounds.getMinExtentPoint() };
    EXPECT_EQ(composite_surface_d_min_extent_actual, composite_surface_d_min_extent_expected);

    const gfx::Vector4 composite_surface_d_max_extent_expected{ gfx::createPoint(4, 7, 4.5) };
    const gfx::Vector4 composite_surface_d_max_extent_actual{ composite_surface_d_bounds.getMaxExtentPoint() };
    EXPECT_EQ(composite_surface_d_max_extent_actual, composite_surface_d_max_extent_expected);
}

// Test setting the material for a composite surface
TEST(GraphicsCompositeSurface, SetMaterial)
{
    const gfx::Material material_a{ gfx::white() };
    const gfx::Sphere sphere_a{ gfx::createTranslationMatrix(0.5, 0, 0), material_a };
    const gfx::Material material_b{ gfx::white() };
    const gfx::Sphere sphere_b{ gfx::createTranslationMatrix(-0.5, 0, 0), material_b };

    gfx::CompositeSurface composite_surface{ sphere_a, sphere_b };

    // Test that a composite surface's material is applied to all child objects
    const gfx::Material glassy_material{ gfx::createGlassyMaterial() };
    composite_surface.addMaterial(glassy_material);

    EXPECT_EQ(dynamic_cast<const gfx::Shape&>(composite_surface.getChildAt(0)).getMaterial(), glassy_material);
    EXPECT_EQ(dynamic_cast<const gfx::Shape&>(composite_surface.getChildAt(1)).getMaterial(), glassy_material);

    // Test that removing the material allows child objects to return their own material
    composite_surface.removeMaterial();
    EXPECT_EQ(dynamic_cast<const gfx::Shape&>(composite_surface.getChildAt(0)).getMaterial(), material_a);
    EXPECT_EQ(dynamic_cast<const gfx::Shape&>(composite_surface.getChildAt(1)).getMaterial(), material_b);

    // Test that setting the material at the root of a composite surface tree propagates to all children
    gfx::CompositeSurface nested_composite_surface{ composite_surface, composite_surface };
    nested_composite_surface.addMaterial(glassy_material);
    EXPECT_EQ(
            dynamic_cast<const gfx::Shape&>(
            dynamic_cast<const gfx::CompositeSurface&>(
            nested_composite_surface.getChildAt(0)).getChildAt(1)).getMaterial(), glassy_material);
}

// Tests intersecting a ray with an empty composite surface
TEST(GraphicsCompositeSurface, RayEmptyCompositeSurfaceIntersection)
{
    const gfx::CompositeSurface composite_surface{ };
    const gfx::Ray ray{ 0, 0, 0,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> intersections{ composite_surface.getObjectIntersections(ray) };

    EXPECT_TRUE(intersections.empty());
}

// Tests intersecting a ray with a non-empty composite surface
TEST(GraphicsCompositeSurface, RayCompositeSurfaceIntersection)
{
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ gfx::createTranslationMatrix(0, 0, -3) };
    const gfx::Sphere sphere_c{ gfx::createTranslationMatrix(5, 0, 0) };
    const gfx::CompositeSurface composite_surface{ sphere_a, sphere_b, sphere_c };
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> intersections{ composite_surface.getObjectIntersections(ray) };

    ASSERT_EQ(intersections.size(), 4);
    EXPECT_EQ(intersections.at(0).getObject(), sphere_b);
    EXPECT_EQ(intersections.at(1).getObject(), sphere_b);
    EXPECT_EQ(intersections.at(2).getObject(), sphere_a);
    EXPECT_EQ(intersections.at(3).getObject(), sphere_a);
}

// Tests intersecting a ray with a non-empty composite surface with a transformation applied
TEST(GraphicsCompositeSurface, RayTransformedCompositeSurfaceIntersection)
{
    const gfx::Sphere sphere{ gfx::createTranslationMatrix(5, 0, 0) };
    const gfx::CompositeSurface composite_surface{ gfx::createScalingMatrix(2),
                                       sphere };
    const gfx::Ray ray{ 10, 0, -10,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> intersections{ composite_surface.getObjectIntersections(ray) };

    EXPECT_EQ(intersections.size(), 2);
}

// Tests finding the normal on a child object
TEST(GraphicsCompositeSurface, GetSurfaceNormalChildObject)
{
    const std::shared_ptr<gfx::Sphere> sphere_ptr{
        std::make_shared<gfx::Sphere>(gfx::createTranslationMatrix(5, 0, 0))
    };
    const gfx::CompositeSurface composite_surface_child{ gfx::createScalingMatrix(1, 2, 3), sphere_ptr };
    const gfx::CompositeSurface composite_surface_parent{ gfx::createYRotationMatrix(M_PI_2), composite_surface_child };

    const gfx::Vector4 point{ gfx::createPoint(1.7321, 1.1547, -5.5774) };

    const gfx::Vector4 normal_expected{ gfx::createVector(0.285704, 0.428543, -0.857160) };
    const gfx::Vector4 normal_actual{ sphere_ptr->getSurfaceNormalAt(point) };

    EXPECT_EQ(normal_actual, normal_expected);
}

#pragma clang diagnostic pop