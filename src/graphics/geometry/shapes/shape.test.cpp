#include "gtest/gtest.h"
#include "shape.hpp"

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

class TestShape : public gfx::Shape
{
public:
    TestShape() = default;
    explicit TestShape(const gfx::Matrix4& transform)
            : Shape{ transform }, m_transformed_ray{ }
    {}
    explicit TestShape(const gfx::Material& material)
            : Shape{ material }, m_transformed_ray{ }
    {}
    TestShape(const gfx::Matrix4& transform, const gfx::Material& material)
            : Shape{ transform, material }, m_transformed_ray{ }
    {}

    [[nodiscard]] gfx::BoundingBox getBounds() const override
    { return gfx::BoundingBox{ -1, -1, -1,
                               1, 1, 1 }; }

    [[nodiscard]] std::shared_ptr<Object> clone() const override
    { return std::make_shared<TestShape>(*this); }

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

    [[nodiscard]] bool areEquivalent(const Object& other_shape) const override
    {
        const TestShape& other_test_shape{ dynamic_cast<const TestShape&>(other_shape) };

        return
                this->getTransform() == other_test_shape.getTransform() &&
                this->getMaterial() == other_test_shape.getMaterial();
    }
};

// Tests the base class default constructor
TEST(GraphicsShape, BaseClassDefaultConstructor)
{
    const TestShape shape{ };
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ };

    ASSERT_EQ(shape.getTransform(), transform_expected);
    ASSERT_EQ(shape.getMaterial(), material_expected);
    ASSERT_FALSE(shape.hasParent());
    ASSERT_EQ(shape.getParent(), nullptr);
}

// Tests the base class transform constructor
TEST(GraphicsShape, BaseClassTransformConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ };
    const TestShape shape{ transform_expected };

    ASSERT_EQ(shape.getTransform(), transform_expected);
    ASSERT_EQ(shape.getMaterial(), material_expected);
    ASSERT_FALSE(shape.hasParent());
    ASSERT_EQ(shape.getParent(), nullptr);
}

// Tests the base class material constructor
TEST(GraphicsShape, BaseClassMaterialConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
    const gfx::Material material_expected{ gfx::Color{ 0.5, 0.5, 0.5 } };
    const TestShape shape{ material_expected };

    ASSERT_EQ(shape.getTransform(), transform_expected);
    ASSERT_EQ(shape.getMaterial(), material_expected);
    ASSERT_FALSE(shape.hasParent());
    ASSERT_EQ(shape.getParent(), nullptr);
}

// Tests the base class standard constructor
TEST(GraphicsShape, BaseClassStandardConstructor)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    const gfx::Material material_expected{ gfx::Color{ 0.5, 0.5, 0.5 }  };
    const TestShape shape{ transform_expected, material_expected };

    ASSERT_EQ(shape.getTransform(), transform_expected);
    ASSERT_EQ(shape.getMaterial(), material_expected);
    ASSERT_FALSE(shape.hasParent());
    ASSERT_EQ(shape.getParent(), nullptr);
}

// Tests setting the transform of a shape
TEST(GraphicsShape, SetTransform)
{
    const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
    TestShape shape{ };

    shape.setTransform(transform_expected);

    ASSERT_EQ(shape.getTransform(), transform_expected);
}

// Tests setting the material of a shape
TEST(GraphicsShape, SetMaterial)
{
    const gfx::Material material_expected{ gfx::Color{ 0.5, 0.5, 0.5 }  };
    TestShape shape{ };

    shape.setMaterial(material_expected);

    ASSERT_EQ(shape.getMaterial(), material_expected);
}

// Tests that getIntersections properly transforms a ray to object space before calculating intersections
TEST(GraphicsShape, GetIntersectionsTransformsRay)
{
    // Test intersecting a scaled shape
    const gfx::Ray ray_a_initial{ 0, 0, -5,
                                  0, 0, 1 };
    const TestShape shape_a{ gfx::createScalingMatrix(2) };

    const auto discarded_intersections_a{ shape_a.getObjectIntersections(ray_a_initial) };

    const gfx::Ray ray_a_transformed_expected{ 0, 0, -2.5,
                                               0, 0, 0.5};
    const gfx::Ray ray_a_transformed_actual{ shape_a.getTransformedRay() };
    ASSERT_EQ(ray_a_transformed_actual, ray_a_transformed_expected);

    // Test intersecting a translated shape
    const gfx::Ray ray_b_initial{ 0, 0, -5,
                                  0, 0, 1 };
    const TestShape shape_b{ gfx::createTranslationMatrix(5, 0, 0) };

    const auto discarded_intersections_b{ shape_b.getObjectIntersections(ray_b_initial) };

    const gfx::Ray ray_b_transformed_expected{ -5, 0, -5,
                                               0, 0, 1};
    const gfx::Ray ray_b_transformed_actual{ shape_b.getTransformedRay() };
    ASSERT_EQ(ray_b_transformed_actual, ray_b_transformed_expected);
}

// Tests that getSurfaceNormal transforms a vector to and from object space
TEST(GraphicsShape, GetSurfaceNormalTransformsVector)
{
    // Test calculating the normal on a translated shape
    TestShape shape_a{ gfx::createTranslationMatrix(0, 1, 0) };
    const gfx::Vector4 input_point_a{ 0, 1.707107, -0.707107, 1 };
    const gfx::Vector4 vector_a_transformed_actual{ shape_a.getSurfaceNormalAt(input_point_a) };

    const gfx::Vector4 vector_a_transformed_expected{ 0, 0.707107, -0.707107, 0 };
    ASSERT_EQ(vector_a_transformed_actual, vector_a_transformed_expected);

    // Test calculating the normal on a transformed shape
    TestShape shape_b{ gfx::createScalingMatrix(1, 0.5, 1) * gfx::createZRotationMatrix(M_PI / 5) };
    const gfx::Vector4 input_point_b{ 0, M_PI_2, -M_PI_2, 1 };
    const gfx::Vector4 vector_b_transformed_actual{ shape_b.getSurfaceNormalAt(input_point_b) };

    const gfx::Vector4 vector_b_transformed_expected{ 0, 0.970143, -0.242536, 0 };
    ASSERT_EQ(vector_b_transformed_actual, vector_b_transformed_expected);
}

// Tests getting the color from an object with no pattern
TEST(GraphicsShape, GetObjectColorNoPattern)
{
    const gfx::Material material{ gfx::cyan() };
    const TestShape shape{ material };

    const gfx::Color color_actual{ shape.getObjectColorAt(gfx::createPoint(0, 0, 0))};
    EXPECT_EQ(color_actual, gfx::cyan());
}

// Tests getting the color from objects with patterns in various states
TEST(GraphicsShape, GetObjectColorPattern)
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
    const gfx::Matrix4 pattern_c_transform{ gfx::createScalingMatrix(2) };
    const gfx::StripePattern stripe_pattern_c{ pattern_c_transform, gfx::white(), gfx::black() };
    const gfx::Material material_c{ stripe_pattern_c };
    const gfx::Sphere sphere_c{ material_c };

    const gfx::Color color_actual_c{ sphere_c.getObjectColorAt(gfx::createPoint(1.5, 0, 0))};
    EXPECT_EQ(color_actual_c, gfx::white());

    // Test getting the object color from a stripe-patterned sphere with a pattern and object transformation
    const gfx::Matrix4 pattern_d_transform{ gfx::createTranslationMatrix(0.5, 0, 0) };
    const gfx::StripePattern stripe_pattern_d{ pattern_d_transform, gfx::white(), gfx::black() };
    const gfx::Material material_d{ stripe_pattern_d };
    const gfx::Matrix4 sphere_d_transform{ gfx::createScalingMatrix(2) };
    const gfx::Sphere sphere_d{ sphere_d_transform, material_d };

    const gfx::Color color_actual_d{ sphere_d.getObjectColorAt(gfx::createPoint(2.5, 0, 0))};
    EXPECT_EQ(color_actual_d, gfx::white());
}
