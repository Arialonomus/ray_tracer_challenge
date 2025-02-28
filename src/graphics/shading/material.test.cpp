#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "material.hpp"

#include "color.hpp"
#include "texture.hpp"
#include "color_texture.hpp"
#include "vector3.hpp"
#include "stripe_pattern.hpp"
#include "transform.hpp"

// Tests initialization for material properties
TEST(GraphicsMaterial, MaterialPropertiesInitalization)
{
    // Test default properties initialization
    const double default_ambient_expected{ 0.1 };
    const double default_diffuse_expected{ 0.9 };
    const double default_specular_expected{ 0.9 };
    const double default_shininess_expected{ 200 };
    const double default_reflectivity_expected{ 0 };
    const double default_transparency_expected{ 0 };
    const double default_refractive_index_expected{ 1 };

    const gfx::MaterialProperties default_properties{ };
    EXPECT_FLOAT_EQ(default_properties.ambient, default_ambient_expected);
    EXPECT_FLOAT_EQ(default_properties.diffuse, default_diffuse_expected);
    EXPECT_FLOAT_EQ(default_properties.specular, default_specular_expected);
    EXPECT_FLOAT_EQ(default_properties.shininess, default_shininess_expected);
    EXPECT_FLOAT_EQ(default_properties.reflectivity, default_reflectivity_expected);
    EXPECT_FLOAT_EQ(default_properties.transparency, default_transparency_expected);
    EXPECT_FLOAT_EQ(default_properties.refractive_index, default_refractive_index_expected);

    // Test custom properties initialization
    const double custom_ambient_expected{ 0.5 };
    const double custom_diffuse_expected{ 0.5 };
    const double custom_specular_expected{ 0.5 };
    const double custom_shininess_expected{ 50 };
    const double custom_reflectivity_expected{ 0.5 };
    const double custom_transparency_expected{ 0.5 };
    const double custom_refractive_index_expected{ 0.5 };

    const gfx::MaterialProperties custom_properties{ custom_ambient_expected,
                                                     custom_diffuse_expected,
                                                     custom_specular_expected,
                                                     custom_shininess_expected,
                                                     custom_reflectivity_expected,
                                                     custom_transparency_expected,
                                                     custom_refractive_index_expected };
    EXPECT_FLOAT_EQ(custom_properties.ambient, custom_ambient_expected);
    EXPECT_FLOAT_EQ(custom_properties.diffuse, custom_diffuse_expected);
    EXPECT_FLOAT_EQ(custom_properties.specular, custom_specular_expected);
    EXPECT_FLOAT_EQ(custom_properties.shininess, custom_shininess_expected);
    EXPECT_FLOAT_EQ(custom_properties.reflectivity, custom_reflectivity_expected);
    EXPECT_FLOAT_EQ(custom_properties.transparency, custom_transparency_expected);
    EXPECT_FLOAT_EQ(custom_properties.refractive_index, custom_refractive_index_expected);
}

// Tests the material properties equality operator
TEST(GraphicsMaterial, MaterialPropertiesEqualityOperator)
{
    const gfx::MaterialProperties default_properties_a{ }, default_properties_b{ };
    EXPECT_TRUE(default_properties_a == default_properties_b);

    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const double transparency_expected{ 0.5 };
    const double refractive_index_expected{ 0.5 };

    const gfx::MaterialProperties custom_properties_a{
        .ambient = ambient_expected,
        .diffuse = diffuse_expected,
        .specular = specular_expected,
        .shininess = shininess_expected,
        .reflectivity = reflectivity_expected,
        .transparency = transparency_expected,
        .refractive_index = refractive_index_expected
    };
    const gfx::MaterialProperties custom_properties_b{
            .ambient = ambient_expected,
            .diffuse = diffuse_expected,
            .specular = specular_expected,
            .shininess = shininess_expected,
            .reflectivity = reflectivity_expected,
            .transparency = transparency_expected,
            .refractive_index = refractive_index_expected
    };
    EXPECT_TRUE(custom_properties_a == custom_properties_b);
}

// Tests the default constructor
TEST(GraphicsMaterial, DefaultConstructor)
{
    const gfx::ColorTexture texture_expected{ };
    const gfx::MaterialProperties properties_expected{ };

    const gfx::Material material{ };

    const gfx::Vector4 test_point{ gfx::createPoint(0, 0, 0) };
    const gfx::Color color_expected{ 1, 1, 1 };
    EXPECT_EQ(material.getTexture(), texture_expected);
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point, gfx::ProjectionMap), color_expected);
    EXPECT_EQ(material.getProperties(), properties_expected);
}

// Tests the color constructors
TEST(GraphicsMaterial, ColorConstructors)
{
    const double color_r{ 0.5 }, color_g{ 0.5 }, color_b{ 0.5 };
    const gfx::Color color_expected{ color_r, color_g, color_b };
    const gfx::ColorTexture texture_expected{ color_expected };
    const gfx::MaterialProperties properties_expected{ };

    // Test the color object constructor
    const gfx::Material material_a{ color_expected };

    const gfx::Vector4 test_point{ gfx::createPoint(0, 0, 0) };
    EXPECT_EQ(material_a.getTexture(), texture_expected);
    EXPECT_EQ(material_a.getTexture().getTextureColorAt(test_point, gfx::ProjectionMap), color_expected);
    EXPECT_EQ(material_a.getProperties(), properties_expected);

    // Test the float list constructor
    const gfx::Material material_b{ color_r, color_g, color_b };

    EXPECT_EQ(material_b.getTexture(), texture_expected);
    EXPECT_EQ(material_b.getTexture().getTextureColorAt(test_point, gfx::ProjectionMap), color_expected);
    EXPECT_EQ(material_b.getProperties(), properties_expected);
}

// Tests the texture constructor
TEST(GraphicsMaterial, TextureConstructor)
{
    const gfx::StripePattern pattern_expected{ gfx::createScalingMatrix(5),
                                               gfx::white(),
                                               gfx::black() };
    const gfx::MaterialProperties properties_expected{ };
    
    const gfx::Material material{ pattern_expected };

    // Test that the pattern texture is applied and properly initialized
    EXPECT_EQ(material.getTexture(), pattern_expected);
    const gfx::Vector4 test_point_a{ gfx::createPoint(0, 0, 0) };
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point_a, gfx::ProjectionMap), gfx::white());
    const gfx::Vector4 test_point_b{ gfx::createPoint(5, 0, 0) };
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point_b, gfx::ProjectionMap), gfx::black());
    EXPECT_EQ(material.getProperties(), properties_expected);
}

// Tests the material properties list-only constructor
TEST(GraphicsMaterial, MaterialPropertiesConstructor)
{
    const gfx::ColorTexture texture_expected{ };
    const gfx::Color color_expected{ 1, 1, 1 };

    // Test building an opaque material
    const double opaque_transparency_expected{ 0 };
    const double opaque_refractive_index_expected{ 1 };
    const gfx::MaterialProperties opaque_properties{ .ambient = 0.5,
                                                     .diffuse = 0.5,
                                                     .specular = 0.5,
                                                     .shininess = 50,
                                                     .reflectivity = 0.5 };
    const gfx::Material opaque_material{ opaque_properties };

    // Test that the default texture is applied and properly initialized
    const gfx::Vector4 test_point{ gfx::createPoint(0, 0, 0) };
    EXPECT_EQ(opaque_material.getTexture(), texture_expected);
    EXPECT_EQ(opaque_material.getTexture().getTextureColorAt(test_point, gfx::ProjectionMap), color_expected);

    // Test that unspecified material properties are correctly initialized
    EXPECT_EQ(opaque_material.getProperties(), opaque_properties);
    EXPECT_FLOAT_EQ(opaque_material.getProperties().transparency, opaque_transparency_expected);
    EXPECT_FLOAT_EQ(opaque_material.getProperties().refractive_index, opaque_refractive_index_expected);

    // Test building a transparent material
    const gfx::MaterialProperties transparent_properties{ .ambient = 0.5,
                                                          .diffuse = 0.5,
                                                          .specular = 0.5,
                                                          .shininess = 50,
                                                          .reflectivity = 0.5,
                                                          .transparency = 1,
                                                          .refractive_index = 0.5 };
    const gfx::Material transparent_material{ transparent_properties };

    // Test that the default texture is applied and properly initialized
    EXPECT_EQ(transparent_material.getTexture(), texture_expected);
    EXPECT_EQ(transparent_material.getTexture().getTextureColorAt(test_point, gfx::ProjectionMap), color_expected);

    // Test that material properties are correctly initialized
    EXPECT_EQ(transparent_material.getProperties(), transparent_properties);
}

// Tests the copy constructor
TEST(GraphicsMaterial, CopyConstructor)
{
    const gfx::ColorTexture texture_expected{ 0.5, 0.5, 0.5 };
    const gfx::MaterialProperties properties_expected{ .ambient = 0.5,
                                                       .diffuse = 0.5,
                                                       .specular = 0.5,
                                                       .shininess = 50,
                                                       .reflectivity = 0.5,
                                                       .transparency = 1,
                                                       .refractive_index = 0.5 };
    const gfx::Material material_src{ texture_expected, properties_expected };
    const gfx::Material material_cpy{ material_src };

    EXPECT_EQ(material_cpy.getTexture(), texture_expected);
    EXPECT_EQ(material_cpy.getProperties(), properties_expected);
}

// Tests the assignment operator
TEST(GraphicsMaterial, AssignmentOperator)
{
    const gfx::ColorTexture texture_expected{ 0.5, 0.5, 0.5 };
    const gfx::MaterialProperties properties_expected{ .ambient = 0.5,
                                                       .diffuse = 0.5,
                                                       .specular = 0.5,
                                                       .shininess = 50,
                                                       .reflectivity = 0.5,
                                                       .transparency = 1,
                                                       .refractive_index = 0.5 };
    const gfx::Material material_a{ texture_expected, properties_expected };
    gfx::Material material_b{ };

    material_b = material_a;

    EXPECT_EQ(material_b.getTexture(), texture_expected);
    EXPECT_EQ(material_b.getProperties(), properties_expected);
}

// Tests the equality operator
TEST(GraphicsMaterial, EqualityOperator)
{
const gfx::Material material_a{ };
const gfx::Material material_b{ };

EXPECT_TRUE(material_a == material_b);
}

// Tests the inequality operator
TEST(GraphicsMaterial, InequalityOperator)
{
    const gfx::ColorTexture material_a_texture{ 0.5, 0.5, 0.5 };
    const gfx::MaterialProperties material_a_properties{ .ambient = 0.5,
                                                       .diffuse = 0.5,
                                                       .specular = 0.5,
                                                       .shininess = 50,
                                                       .reflectivity = 0.5,
                                                       .transparency = 1,
                                                       .refractive_index = 0.5 };
    const gfx::Material material_a{ material_a_texture, material_a_properties };
    const gfx::Material material_b{ };

    EXPECT_TRUE(material_a != material_b);
}

// Tests mutator methods
TEST(GraphicsMaterial, Mutators)
{
    gfx::Material material{ };

    // setPattern (Copy Semantics)
    const gfx::StripePattern pattern_expected{ gfx::createScalingMatrix(5),
                                               gfx::white(),
                                               gfx::black() };
    material.setTexture(pattern_expected);
    EXPECT_EQ(material.getTexture(), pattern_expected);

    // setPattern (Pointer Copy Semantics)
    const gfx::ColorTexture default_texture{ };
    const std::shared_ptr<gfx::Texture> default_texture_ptr{ default_texture.clone() };
    material.setTexture(default_texture_ptr);
    EXPECT_EQ(material.getTexture(), default_texture);

    // setPattern (Move Semantics)
    material.setTexture(std::make_shared<gfx::StripePattern>(
            gfx::createScalingMatrix(5),
            gfx::white(),
            gfx::black()
            ));
    EXPECT_EQ(material.getTexture(), pattern_expected);
}

// Tests creating a glassy material using the factory function
TEST(GraphicsMaterial, CreateGlassyMaterial)
{
    const gfx::Material glassy_material{ gfx::createGlassyMaterial() };
    EXPECT_FLOAT_EQ(glassy_material.getProperties().transparency, 1);
    EXPECT_FLOAT_EQ(glassy_material.getProperties().refractive_index, 1.5);
}

#pragma clang diagnostic pop