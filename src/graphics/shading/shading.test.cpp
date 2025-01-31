#include "gtest/gtest.h"
#include "shading_functions.hpp"

#include <cmath>

#include "material.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "vector4.hpp"
#include "stripe_pattern.hpp"

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
    const gfx::Material material{ stripe_pattern,
                                  1,
                                  0,
                                  0,
                                  200 };
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