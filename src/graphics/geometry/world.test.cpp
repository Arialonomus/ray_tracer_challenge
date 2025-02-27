#include "gtest/gtest.h"
#include "world.hpp"

#include <vector>

#include "light.hpp"
#include "surface.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "intersection.hpp"
#include "plane.hpp"
#include "texture_map.hpp"

static const gfx::World default_world {
    gfx::PointLight { gfx::Color{ 1, 1, 1 },
                      gfx::createPoint( -10, 10, -10 ) },
    gfx::Sphere {
        gfx::Material{ gfx::Color{ 0.8, 1.0, 0.6 },
                       0.1, 0.7, 0.2, 200,
                       0, 0, 1 }
        },
    gfx::Sphere { gfx::createScalingMatrix(0.5) }
};

// Tests the default constructor
TEST(GraphicsWorld, DefaultConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 1, 1, 1 },
                                    gfx::createPoint(-10, 10, -10) };
    const gfx::World world{ };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_TRUE(world.isEmpty());
}

// Tests the point light constructor
TEST(GraphicsWorld, PointLightConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 0.5, 0.5, 0.5 },
                                           gfx::createPoint(-5, 5, -5) };
    const gfx::World world{ light_source_expected };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_TRUE(world.isEmpty());
}

// Tests the object list constructor (single object)
TEST(GraphicsWorld, ObjectListConstructorSingleObject)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 1, 1, 1 },
                                           gfx::createPoint(-10, 10, -10) };
    gfx::Sphere sphere_a{ };
    const gfx::World world{ sphere_a };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_EQ(world.getObjectCount(), 1);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(world.getObjectAt(0)), sphere_a);
}

// Tests the object list constructor (multiple objects)
TEST(GraphicsWorld, ObjectListConstructorMultipleObjects)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 1, 1, 1 },
                                                 gfx::createPoint(-10, 10, -10) };
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ };
    const gfx::World world{ sphere_a, sphere_b };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_EQ(world.getObjectCount(), 2);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(world.getObjectAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(world.getObjectAt(1)), sphere_b);
}

// Tests the standard constructor
TEST(GraphicsWorld, StandardConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 0.5, 0.5, 0.5 },
                                                 gfx::createPoint(-5, 5, -5) };
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ };
    const gfx::World world{ light_source_expected, sphere_a, sphere_b };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_EQ(world.getObjectCount(), 2);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(world.getObjectAt(0)), sphere_a);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(world.getObjectAt(1)), sphere_b);
}

// Tests getting the number of objects in the world
TEST(GraphicsWorld, GetObjectCount)
{
    // Test the object count of an empty world
    const gfx::World world_a{ };

    ASSERT_EQ(world_a.getObjectCount(), 0);
    ASSERT_TRUE(world_a.isEmpty());

    // Test the object count of a populated world
    const gfx::Sphere sphere_a{ };
    const gfx::Sphere sphere_b{ };
    const gfx::Sphere sphere_c{ };
    const gfx::World world_b{ sphere_a, sphere_b, sphere_c };

    ASSERT_EQ(world_b.getObjectCount(), 3);
}

// Tests adding an object to the world
TEST(GraphicsWorld, AddObject)
{
    gfx::World world{ };
    const gfx::Sphere sphere_a{ };

    world.addObject(sphere_a);

    ASSERT_EQ(world.getObjectCount(), 1);
    ASSERT_EQ(dynamic_cast<const gfx::Sphere&>(world.getObjectAt(0)), sphere_a);
}

// Tests calculating world intersections
TEST(GraphicsWorld, WorldIntersections)
{
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5) };
    const gfx::World world{ sphere_a, sphere_b };
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };

    EXPECT_EQ(world_intersections.size(), 4);
    EXPECT_FLOAT_EQ(world_intersections.at(0).getT(), 4);
    EXPECT_FLOAT_EQ(world_intersections.at(1).getT(), 4.5);
    EXPECT_FLOAT_EQ(world_intersections.at(2).getT(), 5.5);
    EXPECT_FLOAT_EQ(world_intersections.at(3).getT(), 6);
}

// Tests calculating whether various points are in shadow
TEST(GraphicsWorld, PointIsShadowed)
{
    // Test a point where nothing is collinear with point and light source
    ASSERT_FALSE(default_world.isShadowed(gfx::createPoint(0, 10, 0)));

    // Test a point where an object is between the point and the light
    ASSERT_TRUE(default_world.isShadowed(gfx::createPoint(10, -10, 10)));

    // Test a point where the light source is between the point and an object
    ASSERT_FALSE(default_world.isShadowed(gfx::createPoint(-20, 20, -20)));

    // Test a point where the point is between an object and the light source
    ASSERT_FALSE(default_world.isShadowed(gfx::createPoint(-2, 2, -2)));
}

// Test shading a color when a ray misses all objects in a world
TEST(GraphicsWorld, CalculatePixelColorMiss)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 1, 0 };

    const gfx::Color pixel_color_expected{ 0, 0, 0 };
    const gfx::Color pixel_color_actual{ default_world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Test shading a color when a ray hits an object in world from the outside
TEST(GraphicsWorld, CalculatePixelColorHitOutside)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const gfx::Color pixel_color_expected{ 0.380661, 0.475827, 0.285496  };
    const gfx::Color pixel_color_actual{ default_world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Test shading a color when a ray hits an object in world from the inside
TEST(GraphicsWorld, CalculatePixelColorHitInside)
{
    gfx::Material material{ gfx::Color{ 0.8, 1.0, 0.6 } };
    material.setDiffuse(0.7);
    material.setSpecular(0.2);

    gfx::Sphere sphere_a{ material };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5) };
    const gfx::PointLight light_source{ gfx::Color{ 1, 1, 1 },
                                        gfx::createPoint( 0, 0.25, 0 )};
    const gfx::World world{ light_source, sphere_a, sphere_b };
    const gfx::Ray ray{ 0, 0, 0,
                        0, 0, 1 };

    const gfx::Color pixel_color_expected{ 0.904984, 0.904984, 0.904984  };
    const gfx::Color pixel_color_actual{ world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Test shading a color when a ray intersection is behind the ray origin
TEST(GraphicsWorld, CalculatePixelColorHitBehind)
{
    gfx::Material sphere_a_material{ gfx::Color{ 0.8, 1.0, 0.6 } };
    sphere_a_material.setAmbient(1);
    sphere_a_material.setDiffuse(0.7);
    sphere_a_material.setSpecular(0.2);

    gfx::Material sphere_b_material{ };
    sphere_b_material.setAmbient(1);

    gfx::Sphere sphere_a{ sphere_a_material };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5), sphere_b_material };
    const gfx::PointLight light_source{ gfx::Color{ 1, 1, 1 },
                                        gfx::createPoint( 0, 0.25, 0 )};
    const gfx::World world{ light_source, sphere_a, sphere_b };
    const gfx::Ray ray{ 0, 0, 0.75,
                        0, 0, -1 };

    const gfx::Color pixel_color_expected{ gfx::white() };
    const gfx::Color pixel_color_actual{ world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Tests shading a color when a ray intersection point is in shadow
TEST(GraphicsWorld, CalculatePixelColorInShadow)
{
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ gfx::createTranslationMatrix(0, 0, 10) };
    const gfx::PointLight light_source{ gfx::Color{ 1, 1, 1 },
                                        gfx::createPoint( 0, 0, -10 )};
    const gfx::World world{ light_source, sphere_a, sphere_b };
    const gfx::Ray ray{ 0, 0, 5,
                        0, 0, 1 };

    // Validate state is correctly initialized before repeating this calculation in calculatePixelColor()
    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };
    auto possible_hit{ getHit(world_intersections) };

    ASSERT_TRUE(possible_hit);
    const gfx::Intersection intersection_expected{ 4, dynamic_cast<const gfx::Surface*>(&world.getObjectAt(1)) };
    const gfx::Intersection& intersection_actual{ possible_hit.value() };

    EXPECT_EQ(intersection_actual, intersection_expected);

    const gfx::Color pixel_color_expected{ 0.1, 0.1, 0.1 };
    const gfx::Color pixel_color_actual{ world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Tests calculating the reflected color for a non-reflective material
TEST(GraphicsWorld, CalculateReflectedColorNonReflective)
{
    const gfx::Ray ray{ 0, 0, 1,
                        0, 0, 1 };

    const gfx::Intersection base_intersection{ 1, dynamic_cast<const gfx::Surface*>(&default_world.getObjectAt(1)) };
    const gfx::DetailedIntersection detailed_intersection{ base_intersection, ray };

    const gfx::Color color_expected{ gfx::black() };
    const gfx::Color color_actual{ default_world.calculateReflectedColorAt(detailed_intersection) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating the reflected color for a reflective material
TEST(GraphicsWorld, CalculateReflectedColorReflective)
{
    gfx::World world{ default_world };

    gfx::Material plane_material{ };
    plane_material.setReflectivity(0.5);
    const gfx::Plane plane{ gfx::createTranslationMatrix(0, -1, 0), plane_material };
    world.addObject(plane);

    const gfx::Ray ray{ 0, 0, -3,
                        0, -M_SQRT2 / 2, M_SQRT2 /2 };

    const gfx::DetailedIntersection intersection{ gfx::Intersection{ M_SQRT2, &plane }, ray };

    const gfx::Color color_expected{ 0.190331, 0.237913, 0.142748 };
    const gfx::Color color_actual{ world.calculateReflectedColorAt(intersection) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests shading a color on a surface with a reflective material
TEST(GraphicsWorld, CalculatePixelColorReflectiveMaterial)
{
    gfx::World world{ default_world };

    gfx::Material plane_material{ };
    plane_material.setReflectivity(0.5);
    const gfx::Plane plane{ gfx::createTranslationMatrix(0, -1, 0), plane_material };
    world.addObject(plane);

    const gfx::Ray ray{ 0, 0, -3,
                        0, -M_SQRT2 / 2, M_SQRT2 / 2 };

    // Validate state is correctly initialized before repeating this calculation in calculatePixelColor()
    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };
    auto possible_hit{ getHit(world_intersections) };

    ASSERT_TRUE(possible_hit);
    const gfx::Intersection intersection_expected{ M_SQRT2, dynamic_cast<const gfx::Surface*>(&world.getObjectAt(2)) };
    const gfx::Intersection& intersection_actual{ possible_hit.value() };

    EXPECT_EQ(intersection_actual, intersection_expected);

    const gfx::Color pixel_color_expected{ 0.876756, 0.924339, 0.829173 };
    const gfx::Color pixel_color_actual{ world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Tests calculating the refracted color for an opaque material
TEST(GraphicsWorld, CalculateRefractedColorOpaque)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> world_intersections{ default_world.getAllIntersections(ray) };
    const gfx::DetailedIntersection hit{ world_intersections[0], ray };

    const gfx::Color color_expected{ gfx::black() };
    const gfx::Color color_actual{ default_world.calculateRefractedColorAt(hit, world_intersections) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating the refracted color at the maximum recursive depth
TEST(GraphicsWorld, CalculateRefractedColorMaximumDepth)
{
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> world_intersections{ default_world.getAllIntersections(ray) };
    const gfx::DetailedIntersection hit{ world_intersections[0], ray };

    const gfx::Color color_expected{ gfx::black() };
    const gfx::Color color_actual{ default_world.calculateRefractedColorAt(hit,
                                                                           world_intersections,
                                                                           0) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating the refracted color under total internal reflection
TEST(GraphicsWorld, CalculateRefractedColorTotalInternalReflection)
{
    gfx::Material sphere_a_material{ gfx::Color{ 0.8, 1.0, 0.6 } };
    sphere_a_material.setDiffuse(0.7);
    sphere_a_material.setSpecular(0.2);
    sphere_a_material.setTransparency(1);
    sphere_a_material.setRefractiveIndex(1.5);

    gfx::Sphere sphere_a{ sphere_a_material };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5) };
    const gfx::World world{ sphere_a, sphere_b };

    const gfx::Ray ray{ 0, 0, M_SQRT2 / 2,
                        0, 1, 0 };

    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };
    const gfx::DetailedIntersection hit{ world_intersections[1], ray };

    const gfx::Color color_expected{ gfx::black() };
    const gfx::Color color_actual{ world.calculateRefractedColorAt(hit, world_intersections) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating the refracted color using refraction rays
TEST(GraphicsWorld, CalculateRefractedColor)
{
    // The original test spec on p133-134 of "The Ray Tracer Challenge" defines a test pattern that returns
    // a color based on the passed-in coordinates. This functionality is used to ensure rays are properly
    // refracted in this test. Following the redesign of Patterns into Textures which use uv coordinates for
    // sampling, this design was no longer possible. As a temporary solution, these test structures have been added
    // preserve the test functionality
    class RefractionTestTexture : public gfx::Texture {
    public:
        RefractionTestTexture() = default;
        ~RefractionTestTexture() override = default;

        [[nodiscard]] std::shared_ptr<gfx::Texture> clone() const override
        { return std::make_shared<RefractionTestTexture>(*this); }

        [[nodiscard]] gfx::Color sampleTextureAt(const gfx::Vector3& transformed_uv) const override
        { return gfx::Color{ transformed_uv.x(), transformed_uv.y(), transformed_uv.w() }; }

        [[nodiscard]] bool areEquivalent(const Texture& other_texture) const override
        { return true; }
    };
    gfx::TextureMap RefractionTestMap{ [](const gfx::Vector4& point) -> gfx::Vector3 {
        return gfx::Vector3{ point.x(), point.y(), point.z() };
    } };

    gfx::Material sphere_a_material{ RefractionTestTexture{ } };
    sphere_a_material.setAmbient(1);
    sphere_a_material.setDiffuse(0.7);
    sphere_a_material.setSpecular(0.2);

    gfx::Sphere sphere_a{ sphere_a_material, RefractionTestMap };

    gfx::Material sphere_b_material{ };
    sphere_b_material.setTransparency(1);
    sphere_b_material.setRefractiveIndex(1.5);

    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5), sphere_b_material };

    const gfx::World world{ sphere_a, sphere_b };

    const gfx::Ray ray{ 0, 0, 0.1,
                        0, 1, 0 };

    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };
    const gfx::DetailedIntersection hit{ world_intersections[2], ray };

    const gfx::Color color_expected{ 0, 0.998883, 0.047216 };
    const gfx::Color color_actual{ world.calculateRefractedColorAt(hit, world_intersections) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests shading pixels in a refractive (transparent) material
TEST(GraphicsWorld, CalculatePixelColorTransparentMaterial)
{
    gfx::World world{ default_world };

    gfx::Material floor_material{ };
    floor_material.setTransparency(0.5);
    floor_material.setRefractiveIndex(1.5);
    const gfx::Plane floor{ gfx::createTranslationMatrix(0, -1, 0), floor_material };
    world.addObject(floor);

    gfx::Material ball_material{ gfx::Color(1, 0, 0) };
    ball_material.setAmbient(0.5);
    const gfx::Sphere ball{ gfx::createTranslationMatrix(0, -3.5, -0.5), ball_material };
    world.addObject(ball);

    const gfx::Ray ray{ 0, 0, -3,
                        0, -M_SQRT2 / 2, M_SQRT2 / 2 };

    // Validate state is correctly initialized before repeating this calculation in calculatePixelColor()
    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };
    auto possible_hit{ getHit(world_intersections) };

    ASSERT_TRUE(possible_hit);
    const gfx::Intersection intersection_expected{ M_SQRT2, dynamic_cast<const gfx::Surface*>(&world.getObjectAt(2)) };
    const gfx::Intersection& intersection_actual{ possible_hit.value() };

    EXPECT_EQ(intersection_actual, intersection_expected);

    const gfx::Color pixel_color_expected{ 0.936425, 0.686425, 0.686425 };
    const gfx::Color pixel_color_actual{ world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}

// Tests shading pixels in a material that is both refractive and reflective
TEST(GraphicsWorld, CalculatePixelColorReflectiveTransparentMaterial)
{
    gfx::World world{ default_world };

    gfx::Material floor_material{ };
    floor_material.setReflectivity(0.5);
    floor_material.setTransparency(0.5);
    floor_material.setRefractiveIndex(1.5);
    const gfx::Plane floor{ gfx::createTranslationMatrix(0, -1, 0), floor_material };
    world.addObject(floor);

    gfx::Material ball_material{ gfx::Color(1, 0, 0) };
    ball_material.setAmbient(0.5);
    const gfx::Sphere ball{ gfx::createTranslationMatrix(0, -3.5, -0.5), ball_material };
    world.addObject(ball);

    const gfx::Ray ray{ 0, 0, -3,
                        0, -M_SQRT2 / 2, M_SQRT2 / 2 };

    // Validate state is correctly initialized before repeating this calculation in calculatePixelColor()
    const std::vector<gfx::Intersection> world_intersections{ world.getAllIntersections(ray) };
    auto possible_hit{ getHit(world_intersections) };

    ASSERT_TRUE(possible_hit);
    const gfx::Intersection intersection_expected{ M_SQRT2, dynamic_cast<const gfx::Surface*>(&world.getObjectAt(2)) };
    const gfx::Intersection& intersection_actual{ possible_hit.value() };

    EXPECT_EQ(intersection_actual, intersection_expected);

    const gfx::Color pixel_color_expected{ 0.933915, 0.696434, 0.692431 };
    const gfx::Color pixel_color_actual{ world.calculatePixelColor(ray) };

    EXPECT_EQ(pixel_color_actual, pixel_color_expected);
}