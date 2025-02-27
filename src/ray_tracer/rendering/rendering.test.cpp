#include "gtest/gtest.h"
#include "rendering_functions.hpp"

#include <cmath>

#include "color.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "vector4.hpp"
#include "transform.hpp"

// Tests rendering a world to a canvas
TEST(RayTracerRendering, RenderWorld)
{
    gfx::Material material{ gfx::Color{ 0.8, 1.0, 0.6 } };
    material.setDiffuse(0.7);
    material.setSpecular(0.2);

    gfx::Sphere sphere_a{ material };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5) };
    const gfx::World world{ sphere_a, sphere_b };

    const gfx::Vector4 from_position{ gfx::createPoint(0, 0, -5) };
    const gfx::Vector4 to_position{ gfx::createPoint(0, 0, 0) };
    const gfx::Vector4 up_vector{ gfx::createVector(0, 1, 0) };
    const gfx::Matrix4 view_transform_matrix{
            gfx::createViewTransformMatrix(
                    from_position,
                    to_position,
                    up_vector) };
    const rt::Camera camera{ 11, 11, M_PI_2, view_transform_matrix };

    const rt::Canvas image{ rt::render(world, camera) };

    const gfx::Color color_center_pixel_expected{ 0.380661, 0.475827, 0.285496 };
    const gfx::Color color_center_pixel_actual{ image[5, 5] };
    EXPECT_EQ(color_center_pixel_actual, color_center_pixel_expected);
}