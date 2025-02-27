#include "gtest/gtest.h"
#include "surface.hpp"

#include <cmath>
#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "bounding_box.hpp"
#include "vector4.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "transform.hpp"

#include "sphere.hpp"

#include "stripe_pattern.hpp"

class TestSurface : public gfx::Surface
{
public:
    TestSurface() = default;
    explicit TestSurface(const gfx::Matrix4& transform)
            : Surface{ transform }, m_transformed_ray{ }
    {}
    explicit TestSurface(const gfx::Material& material)
            : Surface{ material }, m_transformed_ray{ }
    {}
    TestSurface(const gfx::Matrix4& transform, const gfx::Material& material)
            : Surface{ transform, material }, m_transformed_ray{ }
    {}

    [[nodiscard]] gfx::BoundingBox getBounds() const override
    { return gfx::BoundingBox{ -1, -1, -1,
                               1, 1, 1 }; }

    [[nodiscard]] std::shared_ptr<Object> clone() const override
    { return std::make_shared<TestSurface>(*this); }

    [[nodiscard]] gfx::Ray getTransformedRay() const
    { return m_transformed_ray; }

private:
    mutable gfx::Ray m_transformed_ray{ };

    [[nodiscard]] gfx::Vector4 calculateSurfaceNormal(const gfx::Vector4& transformed_point) const override
    {
        return gfx::createVector(transformed_point.x(), transformed_point.y(), transformed_point.z());
    }

    [[nodiscard]] std::vector<gfx::Intersection> calculateIntersections(const gfx::Ray& transformed_ray) const override
    {
        m_transformed_ray = transformed_ray;
        return std::vector<gfx::Intersection>{ };
    }

    [[nodiscard]] bool areEquivalent(const Object& other_surface) const override
    {
        const TestSurface& other_test_surface{ dynamic_cast<const TestSurface&>(other_surface) };

        return
                this->getTransform() == other_test_surface.getTransform() &&
                this->getMaterial() == other_test_surface.getMaterial();
    }
};

// Tests the base class default constructor
TEST(GraphicsSurface, BaseClassDefaultConstructor)
{
    const TestSurface surface{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    ASSERT_EQ(surface.getTransform(), transform_expected);
    ASSERT_EQ(surface.getMaterial(), material_expected);
    ASSERT_FALSE(surface.hasParent());
    ASSERT_EQ(surface.getParent(), nullptr);
}

// Tests the base class transform constructor
TEST(GraphicsSurface, BaseClassTransformConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };
    const TestSurface surface{ transform_expected };

    ASSERT_EQ(surface.getTransform(), transform_expected);
    ASSERT_EQ(surface.getMaterial(), material_expected);
    ASSERT_FALSE(surface.hasParent());
    ASSERT_EQ(surface.getParent(), nullptr);
}

// Tests the base class material constructor
TEST(GraphicsSurface, BaseClassMaterialConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ gfx::Color{ 0.5, 0.5, 0.5 } };
    const TestSurface surface{ material_expected };

    ASSERT_EQ(surface.getTransform(), transform_expected);
    ASSERT_EQ(surface.getMaterial(), material_expected);
    ASSERT_FALSE(surface.hasParent());
    ASSERT_EQ(surface.getParent(), nullptr);
}

// Tests the base class standard constructor
TEST(GraphicsSurface, BaseClassStandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ gfx::Color{ 0.5, 0.5, 0.5 }  };
    const TestSurface surface{ transform_expected, material_expected };

    ASSERT_EQ(surface.getTransform(), transform_expected);
    ASSERT_EQ(surface.getMaterial(), material_expected);
    ASSERT_FALSE(surface.hasParent());
    ASSERT_EQ(surface.getParent(), nullptr);
}

// Tests setting the transform of a surface
TEST(GraphicsSurface, SetTransform)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    TestSurface surface{ };

    surface.setTransform(transform_expected);

    ASSERT_EQ(surface.getTransform(), transform_expected);
}

// Tests setting the material of a surface
TEST(GraphicsSurface, SetMaterial)
{
    const gfx::Material material_expected{ gfx::Color{ 0.5, 0.5, 0.5 }  };
    TestSurface surface{ };

    surface.setMaterial(material_expected);

    ASSERT_EQ(surface.getMaterial(), material_expected);
}

// Tests that getIntersections properly transforms a ray to object space before calculating intersections
TEST(GraphicsSurface, GetIntersectionsTransformsRay)
{
    // Test intersecting a scaled surface
    const gfx::Ray ray_a_initial{ 0, 0, -5,
                                  0, 0, 1 };
    const TestSurface surface_a{ gfx::createScalingMatrix(2) };

    const auto discarded_intersections_a{ surface_a.getObjectIntersections(ray_a_initial) };

    const gfx::Ray ray_a_transformed_expected{ 0, 0, -2.5,
                                               0, 0, 0.5};
    const gfx::Ray ray_a_transformed_actual{ surface_a.getTransformedRay() };
    ASSERT_EQ(ray_a_transformed_actual, ray_a_transformed_expected);

    // Test intersecting a translated surface
    const gfx::Ray ray_b_initial{ 0, 0, -5,
                                  0, 0, 1 };
    const TestSurface surface_b{ gfx::createTranslationMatrix(5, 0, 0) };

    const auto discarded_intersections_b{ surface_b.getObjectIntersections(ray_b_initial) };

    const gfx::Ray ray_b_transformed_expected{ -5, 0, -5,
                                               0, 0, 1};
    const gfx::Ray ray_b_transformed_actual{ surface_b.getTransformedRay() };
    ASSERT_EQ(ray_b_transformed_actual, ray_b_transformed_expected);
}

// Tests that getSurfaceNormal transforms a vector to and from object space
TEST(GraphicsSurface, GetSurfaceNormalTransformsVector)
{
    // Test calculating the normal on a translated surface
    TestSurface surface_a{ gfx::createTranslationMatrix(0, 1, 0) };
    const gfx::Vector4 input_point_a{ 0, 1.707107, -0.707107, 1 };
    const gfx::Vector4 vector_a_transformed_actual{ surface_a.getSurfaceNormalAt(input_point_a) };

    const gfx::Vector4 vector_a_transformed_expected{ 0, 0.707107, -0.707107, 0 };
    ASSERT_EQ(vector_a_transformed_actual, vector_a_transformed_expected);

    // Test calculating the normal on a transformed surface
    TestSurface surface_b{ gfx::createScalingMatrix(1, 0.5, 1) * gfx::createZRotationMatrix(M_PI / 5) };
    const gfx::Vector4 input_point_b{ 0, M_PI_2, -M_PI_2, 1 };
    const gfx::Vector4 vector_b_transformed_actual{ surface_b.getSurfaceNormalAt(input_point_b) };

    const gfx::Vector4 vector_b_transformed_expected{ 0, 0.970143, -0.242536, 0 };
    ASSERT_EQ(vector_b_transformed_actual, vector_b_transformed_expected);
}

// Tests getting the color from an object with no pattern
TEST(GraphicsSurface, GetObjectColorNoPattern)
{
    const gfx::Material material{ gfx::cyan() };
    const TestSurface surface{ material };

    const gfx::Color color_actual{ surface.getObjectColorAt(gfx::createPoint(0, 0, 0))};
    EXPECT_EQ(color_actual, gfx::cyan());
}

// Tests getting the color from objects with patterns in various states
TEST(GraphicsSurface, GetObjectColorPattern)
{
    // Test getting the object color from a stripe-patterned sphere with no transformations
    const gfx::StripePattern stripe_pattern_a{ gfx::white(), gfx::black() };
    const gfx::Material material_a{ stripe_pattern_a };
    const gfx::Sphere sphere_a{ material_a };

    const gfx::Color color_actual_a{ sphere_a.getObjectColorAt(gfx::createPoint(0, 0, 0))};
    EXPECT_EQ(color_actual_a, gfx::white());

    // Test getting the object color from a stripe-patterned sphere with a pattern transformation
    const gfx::StripePattern stripe_pattern_b{ gfx::white(), gfx::black() };
    const gfx::Material material_b{ stripe_pattern_b };
    const gfx::Matrix4 sphere_b_transform{ gfx::createScalingMatrix(2) };
    const gfx::Sphere sphere_b{ sphere_b_transform, material_b };

    const gfx::Color color_actual_b{ sphere_b.getObjectColorAt(gfx::createPoint(1.5, 0, 0))};
    EXPECT_EQ(color_actual_b, gfx::white());

    // Test getting the object color from a stripe-patterned sphere with a pattern transformation
    const gfx::Matrix3 pattern_c_transform{ gfx::create2DScalingMatrix(2) };
    const gfx::StripePattern stripe_pattern_c{ pattern_c_transform,
                                               gfx::white(), gfx::black() };
    const gfx::Material material_c{ stripe_pattern_c };
    const gfx::Sphere sphere_c{ material_c };

    const gfx::Color color_actual_c{ sphere_c.getObjectColorAt(gfx::createPoint(1.5, 0, 0))};
    EXPECT_EQ(color_actual_c, gfx::white());

    // Test getting the object color from a stripe-patterned sphere with a pattern and object transformation
    const gfx::Matrix3 pattern_d_transform{ gfx::create2DTranslationMatrix(0.5, 0) };
    const gfx::StripePattern stripe_pattern_d{ pattern_d_transform,
                                               gfx::white(), gfx::black() };
    const gfx::Material material_d{ stripe_pattern_d };
    const gfx::Matrix4 sphere_d_transform{ gfx::createScalingMatrix(2) };
    const gfx::Sphere sphere_d{ sphere_d_transform, material_d };

    const gfx::Color color_actual_d{ sphere_d.getObjectColorAt(gfx::createPoint(2.5, 0, 0))};
    EXPECT_EQ(color_actual_d, gfx::white());
}
