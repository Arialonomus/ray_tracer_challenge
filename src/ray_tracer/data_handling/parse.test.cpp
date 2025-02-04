#include "gtest/gtest.h"
#include "parse.hpp"

#include <cmath>

#include <nlohmann/json.hpp>

#include "matrix4.hpp"
#include "transform.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "stripe_pattern.hpp"

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

// Tests creating a plane from parsed JSON data
TEST(RayTracerParse, ParsePlaneData)
{
    const json plane_data{
            { "shape", "plane"},
            { "transform", json::array({ }) },
            { "material", {
                { "color", json::array({ 1, 0.9, 0.9 }) },
                { "ambient", 0.1 },
                { "diffuse", 0.9 },
                { "specular", 0 },
                { "shininess", 200 }
            }}
    };

    const gfx::Material material_expected{ 1, 0.9, 0.9,
                                           0.1,
                                           0.9,
                                           0,
                                           200,
                                           0 };
    const gfx::Plane plane_expected{ material_expected };

    const gfx::Plane plane_actual{ dynamic_cast<const gfx::Plane&>(*data::parseObjectData(plane_data)) };
    EXPECT_EQ(plane_actual, plane_expected);
}

// Tests creating a sphere from parsed JSON data
TEST(RayTracerParse, ParseSphereDataNoPattern)
{
    const json sphere_data{
            { "shape", "sphere"},
            { "transform", json::array({
                { { "type", "translate" }, { "values", json::array({ -0.5, 1, 0.5 }) } }
            })},
            { "material", {
                { "color", json::array({ 0.1, 1, 0.5 }) },
                { "ambient", 0.1 },
                { "diffuse", 0.7 },
                { "specular", 0.3 },
                { "shininess", 200 }
            } }
    };

    const gfx::Material material_expected{ 0.1, 1, 0.5,
                                           0.1,
                                           0.7,
                                           0.3,
                                           200,
                                           0 };
    const gfx::Matrix4 transform_expected{ gfx::createTranslationMatrix(-0.5, 1, 0.5) };
    const gfx::Sphere sphere_expected{ transform_expected, material_expected };

    const gfx::Sphere sphere_actual{ dynamic_cast<const gfx::Sphere&>(*data::parseObjectData(sphere_data)) };
    EXPECT_EQ(sphere_actual, sphere_expected);
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
}