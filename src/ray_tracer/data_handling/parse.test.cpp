#include "gtest/gtest.h"
#include "parse.hpp"

#include <cmath>

#include <nlohmann/json.hpp>

#include "matrix4.hpp"
#include "transform.hpp"

#include "plane.hpp"
#include "sphere.hpp"
#include "cube.hpp"
#include "cylinder.hpp"
#include "cone.hpp"
#include "composite_surface.hpp"

#include "stripe_pattern.hpp"
#include "gradient_pattern.hpp"
#include "ring_pattern.hpp"
#include "checkered_pattern.hpp"

using json = nlohmann::json;

// Tests parsing and creating a translation matrix from JSON data
TEST(RayTracerParse, ParseTranslateMatrixData)
{
    // Test parsing a translation matrix
    const json translate_matrix_data{
            { "type",   "translate" },
            { "values", json::array({ 0, 0, 5 }) }
    };
    const gfx::Matrix4 translate_matrix_expected{ gfx::createTranslationMatrix(0, 0, 5) };
    const gfx::Matrix4 translate_matrix_actual{ data::parseTransformMatrixData(translate_matrix_data) };

    ASSERT_EQ(translate_matrix_actual, translate_matrix_expected);
}

// Tests parsing and creating scaling matrices from JSON data
TEST(RayTracerParse, ParseScalingMatrixData)
{
    // Test parsing a uniform scaling matrix
    const json uniform_scale_matrix_data{
            { "type",   "scale" },
            { "values", json::array({ 10 }) }
    };
    const gfx::Matrix4 uniform_scale_matrix_expected{ gfx::createScalingMatrix(10) };
    const gfx::Matrix4 uniform_scale_matrix_actual{
            data::parseTransformMatrixData(uniform_scale_matrix_data)
    };

    ASSERT_EQ(uniform_scale_matrix_actual, uniform_scale_matrix_expected);

    // Test parsing a non-uniform scaling matrix
    const json scale_matrix_data{
            { "type",   "scale" },
            { "values", json::array({ 2, 4, 6 }) }
    };
    const gfx::Matrix4 scale_matrix_expected{ gfx::createScalingMatrix(2, 4, 6) };
    const gfx::Matrix4 scale_matrix_actual{
            data::parseTransformMatrixData(scale_matrix_data)
    };

    ASSERT_EQ(scale_matrix_actual, scale_matrix_expected);
}

// Tests parsing and creating rotation matrices from JSON data
TEST(RayTracerParse, ParseRotationMatrixData)
{
    // Test parsing an x-axis rotation matrix
    const json x_rotation_matrix_data{
            {"type", "rotate_x"},
            {"values", json::array({M_PI_2})}
    };
    const gfx::Matrix4 x_rotation_matrix_expected{ gfx::createXRotationMatrix(M_PI_2) };
    const gfx::Matrix4 x_rotation_matrix_actual{
            data::parseTransformMatrixData(x_rotation_matrix_data)
    };

    ASSERT_EQ(x_rotation_matrix_actual, x_rotation_matrix_expected);

    // Test parsing a y-axis rotation matrix
    const json y_rotation_matrix_data{
            {"type", "rotate_y"},
            {"values", json::array({M_PI_2})}
    };
    const gfx::Matrix4 y_rotation_matrix_expected{ gfx::createYRotationMatrix(M_PI_2) };
    const gfx::Matrix4 y_rotation_matrix_actual{
            data::parseTransformMatrixData(y_rotation_matrix_data)
    };

    ASSERT_EQ(y_rotation_matrix_actual, y_rotation_matrix_expected);

    // Test parsing a z-axis rotation matrix
    const json z_rotation_matrix_data{
            {"type", "rotate_z"},
            {"values", json::array({M_PI_2})}
    };
    const gfx::Matrix4 z_rotation_matrix_expected{ gfx::createZRotationMatrix(M_PI_2) };
    const gfx::Matrix4 z_rotation_matrix_actual{
        data::parseTransformMatrixData(z_rotation_matrix_data)
    };

    ASSERT_EQ(z_rotation_matrix_actual, z_rotation_matrix_expected);
}

// Tests parsing and creating a skew matrix from JSON data
TEST(RayTracerParse, ParseSkewMatrixData)
{
    // Test parsing a translation matrix
    const json skew_matrix_data{
            { "type",   "skew" },
            { "values", json::array({ 0, 0, 0, 0, 0, 1 }) }
    };
    const gfx::Matrix4 skew_matrix_expected{ gfx::createSkewMatrix(0, 0, 0, 0, 0, 1) };
    const gfx::Matrix4 skew_matrix_actual{ data::parseTransformMatrixData(skew_matrix_data) };

    ASSERT_EQ(skew_matrix_actual, skew_matrix_expected);
}

// Tests that invalid JSON data causes an error
TEST(RayTracerParse, ParseMatrixInvalidJSON)
{
    // Test invalid transform matrix type
    const json error_rotation_matrix_data{
            {"type", "rotate"},
            {"values", json::array({M_PI_2})}
    };

    EXPECT_THROW({
        const gfx::Matrix4 error_rotation_matrix_actual{
                data::parseTransformMatrixData(error_rotation_matrix_data) };
        }, std::invalid_argument);

    // Test invalid number of translate matrix values
    const json error_translate_matrix_data{
            { "type",   "translate" },
            { "values", json::array({ 0, 5 }) }
    };

    EXPECT_THROW({
         const gfx::Matrix4 error_translate_matrix_actual{
                 data::parseTransformMatrixData(error_translate_matrix_data) };
         }, std::invalid_argument);

    // Test invalid number of scale matrix values
    const json error_scale_matrix_data{
            { "type",   "scale" },
            { "values", json::array({ 0, 5 }) }
    };

    EXPECT_THROW({
         const gfx::Matrix4 error_scale_matrix_actual{
                 data::parseTransformMatrixData(error_scale_matrix_data) };
         }, std::invalid_argument);

    // Test invalid number of x-axis rotation matrix values
    const json error_x_rotation_matrix_data{
            { "type",   "rotate_x" },
            { "values", json::array({ 0, 5 }) }
    };

    EXPECT_THROW({
         const gfx::Matrix4 error_y_rotation_matrix_actual{
                 data::parseTransformMatrixData(error_x_rotation_matrix_data) };
         }, std::invalid_argument);

    // Test invalid number of x-axis rotation matrix values
    const json error_y_rotation_matrix_data{
            { "type",   "rotate_y" },
            { "values", json::array({ 0, 5 }) }
    };

    EXPECT_THROW({
         const gfx::Matrix4 error_y_rotation_matrix_actual{
                 data::parseTransformMatrixData(error_y_rotation_matrix_data) };
         }, std::invalid_argument);

    // Test invalid number of x-axis rotation matrix values
    const json error_z_rotation_matrix_data{
            { "type",   "rotate_z" },
            { "values", json::array({ 0, 5 }) }
    };

    EXPECT_THROW({
         const gfx::Matrix4 error_z_rotation_matrix_actual{
                 data::parseTransformMatrixData(error_z_rotation_matrix_data) };
         }, std::invalid_argument);

    // Test invalid number of x-axis rotation matrix values
    const json error_skew_matrix_data{
            { "type",   "skew" },
            { "values", json::array({ 0, 5 }) }
    };

    EXPECT_THROW({
         const gfx::Matrix4 error_skew_matrix_actual{
                 data::parseTransformMatrixData(error_skew_matrix_data) };
         }, std::invalid_argument);
}

// Test building a chained transformation matrix from parsed JSON data
TEST(RayTracerParse, BuildChainedTransformMatrix)
{
    const json transform_data_list{ json::array({
                { { "type", "translate" }, { "values", json::array({ 0, 0, 5 }) } },
                { { "type", "rotate_y" }, { "values", json::array({ -M_PI_4 }) } },
                { { "type", "rotate_x" }, { "values", json::array({ M_PI_2 }) } },
                { { "type", "scale" }, { "values", json::array({ 10, 0.01, 10 }) } }
        })
    };

    const gfx::Matrix4 transform_matrix_expected{
        gfx::createTranslationMatrix(0, 0, 5) *
        gfx::createYRotationMatrix(-M_PI_4) *
        gfx::createXRotationMatrix(M_PI_2) *
        gfx::createScalingMatrix(10, 0.01, 10)
    };
    const gfx::Matrix4 transform_matrix_actual{ data::buildChainedTransformMatrix(transform_data_list) };

    EXPECT_EQ(transform_matrix_actual, transform_matrix_expected);
}

// Tests creating a color object from parsed JSON data
TEST(RayTracerParse, ParseColorData)
{
    const json color_data{ json::array({ 1, 0.9, 0.9 }) };
    const gfx::Color color_expected{ 1, 0.9, 0.9 };

    const gfx::Color color_actual{ data::parseColorData(color_data) };
    EXPECT_EQ(color_actual, color_expected);
}

// Tests creating various patterns from parsed JSON data
TEST(RayTracerParse, ParsePatternData)
{
    // Test creating a stripe pattern
    const json stripe_pattern_data{
            { "type", "stripe"},
            { "transform", json::array({ }) },
            { "color_a", json::array({ 0, 0, 0 }) },
            { "color_b", json::array({ 1, 1, 1 }) },
    };
    const gfx::StripePattern stripe_pattern_expected{ gfx::createIdentityMatrix(),
                                                      gfx::black(),
                                                      gfx::white() };

    const auto stripe_pattern_actual{ data::parsePatternData(stripe_pattern_data) };
    EXPECT_EQ(*stripe_pattern_actual, stripe_pattern_expected);

    // Test creating a gradient pattern
    const json gradient_pattern_data{
            { "type", "gradient"},
            { "transform", json::array({
                                               { { "type", "scale" }, { "values", json::array({ 5 }) } }
                                       }) },
            { "color_a", json::array({ 0, 0, 0 }) },
            { "color_b", json::array({ 1, 1, 1 }) },
    };
    const gfx::GradientPattern gradient_pattern_expected{ gfx::createScalingMatrix(5),
                                                          gfx::black(),
                                                          gfx::white() };

    const auto gradient_pattern_actual{ data::parsePatternData(gradient_pattern_data) };
    EXPECT_EQ(*gradient_pattern_actual, gradient_pattern_expected);

    // Test creating a ring pattern
    const json ring_pattern_data{
            { "type", "ring"},
            { "transform", json::array({
                                               { { "type", "translate" }, { "values", json::array({ 5, 10, 15 }) } }
                                       }) },
            { "color_a", json::array({ 0, 0, 0 }) },
            { "color_b", json::array({ 1, 1, 1 }) },
    };
    const gfx::RingPattern ring_pattern_expected{ gfx::createTranslationMatrix(5, 10, 15),
                                                  gfx::black(),
                                                  gfx::white() };

    const auto ring_pattern_actual{ data::parsePatternData(ring_pattern_data) };
    EXPECT_EQ(*ring_pattern_actual, ring_pattern_expected);

    // Test creating a checkered pattern
    const json checkered_pattern_data{
            { "type", "checkered"},
            { "transform", json::array({
                { { "type", "rotate_z" }, { "values", json::array({ M_PI_4 }) } }
            }) },
            { "color_a", json::array({ 0, 0, 0 }) },
            { "color_b", json::array({ 1, 1, 1 }) },
    };
    const gfx::CheckeredPattern checkered_pattern_expected{ gfx::createZRotationMatrix(M_PI_4),
                                                            gfx::black(),
                                                            gfx::white() };

    const auto checkered_pattern_actual{ data::parsePatternData(checkered_pattern_data) };
    EXPECT_EQ(*checkered_pattern_actual, checkered_pattern_expected);
}

// Tests creating a material object from parsed JSON data
TEST(RayTracerParse, ParseMaterialData)
{
    // Test parsing a material without a pattern
    const json material_data_no_pattern{
            { "color", json::array({ 1, 0.9, 0.9 }) },
            { "ambient", 0.5 },
            { "diffuse", 0.5 },
            { "specular", 1 },
            { "shininess", 5000 },
            { "reflectivity", 0.5 },
            { "transparency", 1 },
            { "refractive_index", 1.25 }
    };

    const gfx::Material material_no_pattern_expected{ 1, 0.9, 0.9,
                                                      0.5,
                                                      0.5,
                                                      1,
                                                      5000,
                                                      0.5,
                                                      1,
                                                      1.25 };
    const gfx::Material material_no_pattern_actual(data::parseMaterialData(material_data_no_pattern));

    EXPECT_EQ(material_no_pattern_actual, material_no_pattern_expected);

    // Test parsing a material with a pattern
    const json material_data_with_pattern{
           { "pattern", {
                { "type", "stripe"},
                { "transform", json::array({ }) },
                { "color_a", json::array({ 0, 0, 0 }) },
                { "color_b", json::array({ 1, 1, 1 }) },
           } },
           { "ambient", 0.5 },
           { "diffuse", 0.5 },
           { "specular", 1 },
           { "shininess", 5000 },
           { "reflectivity", 0.5 },
           { "transparency", 1 },
           { "refractive_index", 1.25 }
       };

    const gfx::StripePattern stripe_pattern_expected{ gfx::black(),
                                                      gfx::white() };

    const gfx::Material material_with_pattern_expected{ stripe_pattern_expected,
                                                        0.5,
                                                        0.5,
                                                        1,
                                                        5000,
                                                        0.5,
                                                        1,
                                                        1.25 };
    const gfx::Material material_with_pattern_actual(data::parseMaterialData(material_data_with_pattern));

    EXPECT_EQ(material_with_pattern_actual, material_with_pattern_expected);
}

// Tests creating a plane from parsed JSON data
TEST(RayTracerParse, ParsePlaneData)
{
    const json plane_data{
            { "shape", "plane"},
            { "transform", json::array({ }) },
            { "material", {
                { "color", json::array({ 1, 0.9, 0.9 }) }
            } }
    };

    const gfx::Material material_expected{ gfx::Color{ 1, 0.9, 0.9 } };
    const gfx::Plane plane_expected{ material_expected };

    const gfx::Plane plane_actual{ dynamic_cast<const gfx::Plane&>(*data::parseObjectData(plane_data)) };
    EXPECT_EQ(plane_actual, plane_expected);
}

// Tests creating a sphere from parsed JSON data
TEST(RayTracerParse, ParseSphereData)
{
    const json sphere_data{
            { "shape", "sphere"},
            { "transform", json::array({
                { { "type", "translate" }, { "values", json::array({ -0.5, 1, 0.5 }) } }
            })},
            { "material", {
                { "color", json::array({ 0.1, 1, 0.5 }) }
            } }
    };

    const gfx::Material material_expected{ gfx::Color{ 0.1, 1, 0.5 } };
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(-0.5, 1, 0.5) };
    const gfx::Sphere sphere_expected{ transform_expected, material_expected };

    const gfx::Sphere sphere_actual{ dynamic_cast<const gfx::Sphere&>(*data::parseObjectData(sphere_data)) };
    EXPECT_EQ(sphere_actual, sphere_expected);
}

// Tests creating a cube from parsed JSON data
TEST(RayTracerParse, ParseCubeData)
{
    const json cube_data{
            { "shape", "cube"},
            { "transform", json::array({
                { { "type", "rotate_y" }, { "values", json::array({ M_PI_2 }) } }
            })},
            { "material", {
                { "color", json::array({ 1, 1, 0.5 }) }
            } }
    };

    const gfx::Material material_expected{ gfx::Color{ 1, 1, 0.5 } };
    const gfx::Matrix4 transform_expected{ gfx::createYRotationMatrix(M_PI_2) };
    const gfx::Cube cube_expected{ transform_expected, material_expected };

    const gfx::Cube cube_actual{ dynamic_cast<const gfx::Cube&>(*data::parseObjectData(cube_data)) };
    EXPECT_EQ(cube_actual, cube_expected);
}

// Tests creating a cylinder from parsed JSON data
TEST(RayTracerParse, ParseCylinderData)
{
    const json cylinder_data{
            { "shape", "cylinder"},
            { "transform", json::array({ }) },
            { "material", {
                { "color", json::array({ 1, 1, 0.5 }) }
            } },
            { "y_min", -2 },
            { "y_max", 2 },
            { "is_closed", true }
    };

    const gfx::Material material_expected{ gfx::Color{ 1, 1, 0.5 } };
    const gfx::Cylinder cylinder_expected{ material_expected, -2, 2, true };

    const gfx::Cylinder cylinder_actual{ dynamic_cast<const gfx::Cylinder&>(*data::parseObjectData(cylinder_data)) };
    EXPECT_EQ(cylinder_actual, cylinder_expected);
}

// Tests creating a cone from parsed JSON data
TEST(RayTracerParse, ParseConeData)
{
    const json cone_data{
            { "shape", "cone"},
            { "transform", json::array({ }) },
            { "material", {
                { "color", json::array({ 1, 1, 0.5 }) }
            } },
    };

    const gfx::Material material_expected{ gfx::Color{ 1, 1, 0.5 } };
    const gfx::Cone cone_expected{ material_expected };

    const gfx::Cone cone_actual{ dynamic_cast<const gfx::Cone&>(*data::parseObjectData(cone_data)) };
    EXPECT_EQ(cone_actual, cone_expected);
}

// Tests building a composite surface from parsed JSON data
TEST(RayTracerParse, BuildCompositeSurface)
{
    const json composite_surface_data{
            { "shape", "composite_surface"},
            { "transform", json::array({
                { { "type", "translate" }, { "values", json::array({ 1, 1, 1 }) } }
            })},
            { "material", {
                { "color", json::array({ 0, 0, 1 }) }
            } },
            { "children", json::array({
                {
                    { "shape", "cube" },
                    { "transform", json::array({
                        { { "type", "rotate_y" },
                          { "values", json::array({ M_PI_2 }) } }
                    }) }
                },
                {
                    { "shape", "sphere"},
                    { "transform", json::array({
                        { { "type", "translate" },
                          { "values", json::array({ -0.5, 0.5, 0.5 }) } }
                    }) }
                }
            }) }
    };

    const gfx::Cube cube{ gfx::createYRotationMatrix(M_PI_2) };
    const gfx::Sphere sphere{ gfx::createTranslationMatrix(-0.5, 0.5, 0.5) };

    gfx::CompositeSurface composite_surface_expected{ gfx::createTranslationMatrix(1, 1, 1),
                                                      cube, sphere};
    const gfx::Material material{ gfx::Color{ 0, 0, 1 } };
    composite_surface_expected.addMaterial(material);

    const auto composite_surface_actual_ptr{ data::parseCompositeSurfaceData(composite_surface_data)};
    EXPECT_EQ(*composite_surface_actual_ptr, composite_surface_expected);
}