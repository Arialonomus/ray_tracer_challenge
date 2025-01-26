#include "gtest/gtest.h"
#include "shading_functions.hpp"

#include <cmath>

#include "color.hpp"
#include "material.hpp"
#include "light.hpp"
#include "vector4.hpp"

// Tests calculating surface color with the view origin between the light and the surface
TEST(GraphicsShading, ViewBetweenLightAndSurface)
{
    const gfx::Material material{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 1.9, 1.9, 1.9 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(material,
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
    const gfx::Material material{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{  0, M_SQRT2f / 2, -M_SQRT2f / 2, 0 };

    const gfx::Color color_expected{ 1.0, 1.0, 1.0 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(material,
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
    const gfx::Material material{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 10, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 0.736396, 0.736396, 0.736396 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(material,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the view origin in the path of the light reflection vector
TEST(GraphicsShading, ViewInPathOfReflectionVector)
{
    const gfx::Material material{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 10, -10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, -M_SQRT2f / 2, -M_SQRT2f / 2, 0 };

    const gfx::Color color_expected{ 1.636385, 1.636385, 1.636385 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(material,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}

// Tests calculating surface color with the surface between the view and the light
TEST(GraphicsShading, SurfaceBetweenViewAndLight)
{
    const gfx::Material material{ };
    const gfx::PointLight point_light{ gfx::Color{ 1, 1, 1 },
                                       gfx::createPoint(0, 0, 10) };
    const gfx::Vector4 surface_position{ 0, 0, 0, 1 };
    const gfx::Vector4 surface_normal{ 0, 0, -1, 0 };
    const gfx::Vector4 view_vector{ 0, 0, -1, 0 };

    const gfx::Color color_expected{ 0.1, 0.1, 0.1 };
    const gfx::Color color_actual{ gfx::calculateSurfaceColor(material,
                                                              point_light,
                                                              surface_position,
                                                              surface_normal,
                                                              view_vector) };

    EXPECT_EQ(color_actual, color_expected);
}
