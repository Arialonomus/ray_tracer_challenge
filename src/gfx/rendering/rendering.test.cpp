#include "gtest/gtest.h"
#include "rendering_functions.hpp"

#include <cmath>

#include "color.hpp"
#include "material.hpp"
#include "light.hpp"
#include "vector4.hpp"
#include "transform.hpp"

// Tests calculating surface color with the view origin between the light and the surface
TEST(GraphicsRendering, ViewBetweenLightAndSurface)
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
TEST(GraphicsRendering, ViewBetweenLightAndSurfaceViewOffset45Degrees)
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
TEST(GraphicsRendering, ViewOppositeSurfaceLightOffset45Degrees)
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
TEST(GraphicsRendering, ViewInPathOfReflectionVector)
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
TEST(GraphicsRendering, SurfaceBetweenViewAndLight)
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

// Tests rendering a world to a canvas
TEST(GraphicsRendering, RenderWorld)
{
    gfx::Material material{ };
    material.setColor(0.8, 1.0, 0.6);
    material.setDiffuse(0.7);
    material.setSpecular(0.2);

    gfx::Sphere sphere_a{ material };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5) };
    const std::vector<std::reference_wrapper<gfx::Sphere>> object_list{ sphere_a, sphere_b };
    const gfx::World world{ object_list };

    const gfx::Vector4 from_position{ gfx::createPoint(0, 0, -5) };
    const gfx::Vector4 to_position{ gfx::createPoint(0, 0, 0) };
    const gfx::Vector4 up_vector{ gfx::createVector(0, 1, 0) };
    const gfx::Matrix4 view_transform_matrix{
            gfx::createViewTransformMatrix(
                    from_position,
                    to_position,
                    up_vector) };
    const gfx::Camera camera{ 11, 11, M_PI_2f,view_transform_matrix };

    const gfx::Canvas image{ gfx::render(world, camera) };

    const gfx::Color color_center_pixel_expected{ 0.380661, 0.475827, 0.285496 };
    const gfx::Color color_center_pixel_actual{ image[5, 5] };
    EXPECT_EQ(color_center_pixel_actual, color_center_pixel_expected);
}