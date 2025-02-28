#include "gtest/gtest.h"
#include "shading_functions.hpp"

#include <cmath>

#include "material.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "vector4.hpp"
#include "transform.hpp"
#include "stripe_pattern.hpp"
#include "intersection.hpp"
#include "world.hpp"

// Tests calculating surface color with the view origin between the light and the surface
TEST(GraphicsShading, ViewBetweenLightAndSurface)
{
    const gfx::Material material{ };
    const gfx::Sphere sphere{ material };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 1.9, 1.9, 1.9 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(sphere,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the view origin between the light
// and the surface and the light offset 45 degrees
TEST(GraphicsShading, ViewBetweenLightAndSurfaceViewOffset45Degrees)
{
    const gfx::Sphere sphere{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{  0, M_SQRT2 / 2, -M_SQRT2 / 2, 0 };

    const gfx::Color color_expected{ 1.0, 1.0, 1.0 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(sphere,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the view origin opposite the surface
// and the light offset 45 degrees
TEST(GraphicsShading, ViewOppositeSurfaceLightOffset45Degrees)
{
    const gfx::Sphere sphere{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 10, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 0.736396, 0.736396, 0.736396 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(sphere,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the view origin in the path of the light reflection vector
TEST(GraphicsShading, ViewInPathOfReflectionVector)
{
    const gfx::Sphere sphere{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 10, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, -M_SQRT2 / 2, -M_SQRT2 / 2, 0 };

    const gfx::Color color_expected{ 1.636396, 1.636396, 1.636396 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(sphere,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the surface between the view and the light
TEST(GraphicsShading, SurfaceBetweenViewAndLight)
{
    const gfx::Sphere sphere{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, 10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 0.1, 0.1, 0.1 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(sphere,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the surface between the view and the light
TEST(GraphicsShading, SurfaceInShadow)
{
    const gfx::Sphere sphere{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 0.1, 0.1, 0.1 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(sphere,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector,
                                                              true) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color on a stripe-patterned surface
TEST(GraphicsShading, StripePatternedSurface)
{
    // Test that pattern color A is shaded properly
    const gfx::StripePattern stripe_pattern{ gfx::white(), gfx::black() };
    const gfx::MaterialProperties properties{ .ambient = 1,
                                              .diffuse = 0,
                                              .specular = 0 };
    const gfx::Material material{ stripe_pattern, properties };
    const gfx::Sphere sphere{ material };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, -10) };
    const gfx::Vector4 surface_position_a{ 0.9, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected_a{ 1, 1, 1 };
    const gfx::Color color_actual_a{ gfx::calculateSurfaceColor(sphere,
                                                                point_light,
                                                                surface_position_a,
                                                                surface_normal,
                                                                view_vector) };

    EXPECT_EQ(color_actual_a, color_expected_a);

    // Test that pattern color B is shaded properly
    const gfx::Vector4 surface_position_b{ 1.1, 0, 0, 1 };

    const gfx::Color color_expected_b{ 0, 0, 0 };
    const gfx::Color color_actual_b{ gfx::calculateSurfaceColor(sphere,
                                                                point_light,
                                                                surface_position_b,
                                                                surface_normal,
                                                                view_vector) };

    EXPECT_EQ(color_actual_b, color_expected_b);
}


// Tests finding the refractive indices at multiple intersections of overlapping spheres with different mediums
TEST(GraphicsShading, GetRefractiveIndexOverlappingSpheres)
{
    const gfx::MaterialProperties glassy_properties_a{ .transparency = 1, .refractive_index = 1.5 };
    const gfx::Material glassy_material_a{ glassy_properties_a };
    const gfx::Sphere glass_sphere_a{ gfx::createScalingMatrix(2),
                                      glassy_material_a };

    const gfx::MaterialProperties glassy_properties_b{ .transparency = 1, .refractive_index = 2.0 };
    const gfx::Material glassy_material_b{ glassy_properties_b };
    const gfx::Sphere glass_sphere_b{ gfx::createTranslationMatrix(0, 0, -0.25),
                                      glassy_material_b };

    const gfx::MaterialProperties glassy_properties_c{ .transparency = 1, .refractive_index = 2.5 };
    const gfx::Material glassy_material_c{ glassy_properties_c };
    const gfx::Sphere glass_sphere_c{ gfx::createTranslationMatrix(0, 0, 0.25),
                                      glassy_material_c };

    const gfx::Ray ray{ 0, 0 , -4,
                        0, 0, 1 };
    const gfx::World world{ glass_sphere_a, glass_sphere_b, glass_sphere_c };

    auto intersections{ world.getAllIntersections(ray) };
    const std::vector<std::pair<double, double>> refractive_indices_expected_list{
        std::pair(1.0, 1.5),
        std::pair(1.5, 2.0),
        std::pair(2.0, 2.5),
        std::pair(2.5, 2.5),
        std::pair(2.5, 1.5),
        std::pair(1.5, 1.0)
    };

    // Ensure test cases are properly initialized for comparison
    ASSERT_EQ(intersections.size(), refractive_indices_expected_list.size());

    // Check that the refractive indices for each ray-object intersection are correct
    for (int i = 0; i < intersections.size(); ++i) {
        auto refracted_indices_actual{ gfx::getRefractiveIndices(intersections[i],
                                                                 intersections) };
        EXPECT_EQ(refracted_indices_actual, refractive_indices_expected_list[i]);
    }
}

// Tests calculating reflectance when total internal reflection occurs
TEST(GraphicsShading, CalculateReflectanceTotalInternalReflection)
{
    const gfx::Sphere glass_sphere{ gfx::createGlassyMaterial() };
    const gfx::Ray ray{ 0, 0, M_SQRT2 / 2,
                        0, 1, 0 };
    const gfx::World world{ glass_sphere };

    const auto intersections{ world.getAllIntersections(ray) };
    const gfx::DetailedIntersection detailed_hit{ intersections[1], ray };

    const auto [ n1, n2 ] { gfx::getRefractiveIndices(detailed_hit, intersections) };

    const double reflectance_expected{ 1 };
    const double reflectance_actual{ gfx::calculateReflectance(detailed_hit.getViewVector(),
                                                               detailed_hit.getSurfaceNormal(),
                                                               n1, n2) };

    EXPECT_FLOAT_EQ(reflectance_actual, reflectance_expected);
}

// Tests calculating reflectance when the surface is struck at a 90-degree angle
TEST(GraphicsShading, CalculateReflectancePerpendicularHit)
{
    const gfx::Sphere glass_sphere{ gfx::createGlassyMaterial() };
    const gfx::Ray ray{ 0, 0, 0,
                        0, 1, 0 };
    const gfx::World world{ glass_sphere };

    const auto intersections{ world.getAllIntersections(ray) };
    const gfx::DetailedIntersection detailed_hit{ intersections[1], ray };

    const auto [ n1, n2 ] { gfx::getRefractiveIndices(detailed_hit, intersections) };

    const double reflectance_expected{ 0.04 };
    const double reflectance_actual{ gfx::calculateReflectance(detailed_hit.getViewVector(),
                                                               detailed_hit.getSurfaceNormal(),
                                                               n1, n2) };

    EXPECT_FLOAT_EQ(reflectance_actual, reflectance_expected);
}

// Tests calculating reflectance when the surface is struck at a small angle (n₂ > n₁)
TEST(GraphicsShading, CalculateReflectanceSmallAngleHit)
{
    const gfx::Sphere glass_sphere{ gfx::createGlassyMaterial() };
    const gfx::Ray ray{ 0, 0.99, -2,
                        0, 0, 1 };
    const gfx::World world{ glass_sphere };

    const auto intersections{ world.getAllIntersections(ray) };
    const gfx::DetailedIntersection detailed_hit{ intersections[0], ray };

    const auto [ n1, n2 ] { gfx::getRefractiveIndices(detailed_hit, intersections) };

    const double reflectance_expected{ 0.48881438 };
    const double reflectance_actual{ gfx::calculateReflectance(detailed_hit.getViewVector(),
                                                               detailed_hit.getSurfaceNormal(),
                                                               n1, n2) };

    EXPECT_FLOAT_EQ(reflectance_actual, reflectance_expected);
}