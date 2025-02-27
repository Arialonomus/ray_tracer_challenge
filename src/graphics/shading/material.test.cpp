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

// Tests the default constructor
TEST(GraphicsMaterial, DefaultConstructor)
{
    const gfx::ColorTexture texture_expected{ };
    const gfx::Color color_expected{ 1, 1, 1 };
    
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const double reflectivity_expected{ 0 };
    const double transparency_expected{ 0 };
    const double refractive_index_expected{ 1 };

    const gfx::Material material{ };

    // Test that the default texture is applied and properly initialized
    const gfx::Vector3 test_point{ gfx::create2DPoint(0, 0) };
    EXPECT_EQ(material.getTexture(), texture_expected);
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point), color_expected);
    
    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(material.getTransparency(), transparency_expected);
    EXPECT_FLOAT_EQ(material.getRefractiveIndex(), refractive_index_expected);
}

// Tests the color-only constructor
TEST(GraphicsMaterial, ColorConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const gfx::ColorTexture texture_expected{ color_expected };
    
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const double reflectivity_expected{ 0 };
    const double transparency_expected{ 0 };
    const double refractive_index_expected{ 1 };
    
    const gfx::Material material{ color_expected };

    // Test that the color texture is applied and properly initialized
    const gfx::Vector3 test_point{ gfx::create2DPoint(0, 0) };
    EXPECT_EQ(material.getTexture(), texture_expected);
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point), color_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(material.getTransparency(), transparency_expected);
    EXPECT_FLOAT_EQ(material.getRefractiveIndex(), refractive_index_expected);
}

// Tests the texture-only constructor
TEST(GraphicsMaterial, TextureOnlyConstructor)
{
    const gfx::StripePattern pattern_expected{ gfx::create2DScalingMatrix(5),
                                                  gfx::white(),
                                                  gfx::black() };
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const double reflectivity_expected{ 0 };
    const double transparency_expected{ 0 };
    const double refractive_index_expected{ 1 };
    
    const gfx::Material material{ pattern_expected };

    // Test that the pattern texture is applied and properly initialized
    EXPECT_EQ(material.getTexture(), pattern_expected);
    const gfx::Vector3 test_point_a{ gfx::create2DPoint(0, 0) };
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point_a), gfx::white());
    const gfx::Vector3 test_point_b{ gfx::create2DPoint(5, 0) };
    EXPECT_EQ(material.getTexture().getTextureColorAt(test_point_b), gfx::black());

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(material.getTransparency(), transparency_expected);
    EXPECT_FLOAT_EQ(material.getRefractiveIndex(), refractive_index_expected);
}

// Tests the material properties list-only constructors
TEST(GraphicsMaterial, MaterialPropertiesList)
{
    const gfx::ColorTexture texture_expected{ };
    const gfx::Color color_expected{ 1, 1, 1 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };

    // Test building an opaque material
    const double opaque_transparency_expected{ 0 };
    const double opaque_refractive_index_expected{ 1 };
    const gfx::Material opaque_material{ ambient_expected,
                                         diffuse_expected,
                                         specular_expected,
                                         shininess_expected,
                                         reflectivity_expected };

    // Test that the default texture is applied and properly initialized
    const gfx::Vector3 test_point{ gfx::create2DPoint(0, 0) };
    EXPECT_EQ(opaque_material.getTexture(), texture_expected);
    EXPECT_EQ(opaque_material.getTexture().getTextureColorAt(test_point), color_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(opaque_material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(opaque_material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(opaque_material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(opaque_material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(opaque_material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(opaque_material.getTransparency(), opaque_transparency_expected);
    EXPECT_FLOAT_EQ(opaque_material.getRefractiveIndex(), opaque_refractive_index_expected);

    // Test building a transparent material
    const double transparent_transparency_expected{ 1 };
    const double transparent_refractive_index_expected{ 0.5 };
    const gfx::Material transparent_material{ ambient_expected,
                                              diffuse_expected,
                                              specular_expected,
                                              shininess_expected,
                                              reflectivity_expected,
                                              transparent_transparency_expected,
                                              transparent_refractive_index_expected };

    // Test that the default texture is applied and properly initialized
    EXPECT_EQ(transparent_material.getTexture(), texture_expected);
    EXPECT_EQ(transparent_material.getTexture().getTextureColorAt(test_point), color_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(transparent_material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(transparent_material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(transparent_material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(transparent_material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(transparent_material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(transparent_material.getTransparency(), transparent_transparency_expected);
    EXPECT_FLOAT_EQ(transparent_material.getRefractiveIndex(), transparent_refractive_index_expected);
}

// Tests the no-texture constructors
TEST(GraphicsMaterial, NoTextureConstructors)
{
    const gfx::Color color_a_expected{ 0.5, 0.5, 0.5 };
    const gfx::ColorTexture texture_a_expected{ color_a_expected };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };

    // Test building an opaque material with the color object constructor
    const double opaque_transparency_expected{ 0 };
    const double opaque_refractive_index_expected{ 1 };
    const gfx::Material opaque_material_a{ color_a_expected,
                                           ambient_expected,
                                           diffuse_expected,
                                           specular_expected,
                                           shininess_expected,
                                           reflectivity_expected };

    // Test that the default texture is applied and properly initialized
    const gfx::Vector3 test_point{ gfx::create2DPoint(0, 0) };
    EXPECT_EQ(opaque_material_a.getTexture(), texture_a_expected);
    EXPECT_EQ(opaque_material_a.getTexture().getTextureColorAt(test_point), color_a_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(opaque_material_a.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(opaque_material_a.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(opaque_material_a.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(opaque_material_a.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(opaque_material_a.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(opaque_material_a.getTransparency(), opaque_transparency_expected);
    EXPECT_FLOAT_EQ(opaque_material_a.getRefractiveIndex(), opaque_refractive_index_expected);

    // Test building a transparent material with the color object constructor
    const double transparent_transparency_expected{ 1 };
    const double transparent_refractive_index_expected{ 0.5 };
    const gfx::Material transparent_material_a{ color_a_expected,
                                                ambient_expected,
                                                diffuse_expected,
                                                specular_expected,
                                                shininess_expected,
                                                reflectivity_expected,
                                                transparent_transparency_expected,
                                                transparent_refractive_index_expected };

    // Test that the default texture is applied and properly initialized
    EXPECT_EQ(transparent_material_a.getTexture(), texture_a_expected);
    EXPECT_EQ(transparent_material_a.getTexture().getTextureColorAt(test_point), color_a_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(transparent_material_a.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(transparent_material_a.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(transparent_material_a.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(transparent_material_a.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(transparent_material_a.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(transparent_material_a.getTransparency(), transparent_transparency_expected);
    EXPECT_FLOAT_EQ(transparent_material_a.getRefractiveIndex(), transparent_refractive_index_expected);

    // Test building an opaque material using the float list constructor
    const double color_r{ 0.5 };
    const double color_g{ 0.5 };
    const double color_b{ 0.5 };
    const gfx::Color color_b_expected{ color_r, color_g, color_b };
    const gfx::ColorTexture texture_b_expected{ color_b_expected };
    const gfx::Material opaque_material_b{ color_r,
                                           color_g,
                                           color_b,
                                           ambient_expected,
                                           diffuse_expected,
                                           specular_expected,
                                           shininess_expected,
                                           reflectivity_expected,
                                           opaque_transparency_expected,
                                           opaque_refractive_index_expected};

    // Test that the default texture is applied and properly initialized
    EXPECT_EQ(opaque_material_b.getTexture(), texture_b_expected);
    EXPECT_EQ(opaque_material_b.getTexture().getTextureColorAt(test_point), color_b_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(opaque_material_b.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(opaque_material_b.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(opaque_material_b.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(opaque_material_b.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(opaque_material_b.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(opaque_material_b.getTransparency(), opaque_transparency_expected);
    EXPECT_FLOAT_EQ(opaque_material_b.getRefractiveIndex(), opaque_refractive_index_expected);

    // Test building a transparent material using the float list constructor
    const gfx::Material transparent_material_b{ color_r,
                                                color_g,
                                                color_b,
                                                ambient_expected,
                                                diffuse_expected,
                                                specular_expected,
                                                shininess_expected,
                                                reflectivity_expected,
                                                transparent_transparency_expected,
                                                transparent_refractive_index_expected};

    // Test that the default texture is applied and properly initialized
    EXPECT_EQ(transparent_material_b.getTexture(), texture_b_expected);
    EXPECT_EQ(transparent_material_b.getTexture().getTextureColorAt(test_point), color_b_expected);

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(transparent_material_b.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(transparent_material_b.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(transparent_material_b.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(transparent_material_b.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(transparent_material_b.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(transparent_material_b.getTransparency(), transparent_transparency_expected);
    EXPECT_FLOAT_EQ(transparent_material_b.getRefractiveIndex(), transparent_refractive_index_expected);
}

// Tests the no-color constructors
TEST(GraphicsMaterial, NoColorConstructor)
{
    const gfx::StripePattern pattern_expected{ gfx::create2DScalingMatrix(5),
                                                  gfx::white(),
                                                  gfx::black() };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };

    // Test building an opaque material
    const double opaque_transparency_expected{ 0 };
    const double opaque_refractive_index_expected{ 1 };
    const gfx::Material opaque_material{ pattern_expected,
                                         ambient_expected,
                                         diffuse_expected,
                                         specular_expected,
                                         shininess_expected,
                                         reflectivity_expected };

    // Test that the pattern texture is applied and properly initialized
    EXPECT_EQ(opaque_material.getTexture(), pattern_expected);
    const gfx::Vector3 test_point_a{ gfx::create2DPoint(0, 0) };
    EXPECT_EQ(opaque_material.getTexture().getTextureColorAt(test_point_a), gfx::white());
    const gfx::Vector3 test_point_b{ gfx::create2DPoint(5, 0) };
    EXPECT_EQ(opaque_material.getTexture().getTextureColorAt(test_point_b), gfx::black());

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(opaque_material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(opaque_material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(opaque_material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(opaque_material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(opaque_material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(opaque_material.getTransparency(), opaque_transparency_expected);
    EXPECT_FLOAT_EQ(opaque_material.getRefractiveIndex(), opaque_refractive_index_expected);

    // Test building a transparent material
    const double transparent_transparency_expected{ 1 };
    const double transparent_refractive_index_expected{ 0.5 };
    const gfx::Material transparent_material{ pattern_expected,
                                              ambient_expected,
                                              diffuse_expected,
                                              specular_expected,
                                              shininess_expected,
                                              reflectivity_expected,
                                              transparent_transparency_expected,
                                              transparent_refractive_index_expected };

    // Test that the pattern texture is applied and properly initialized
    EXPECT_EQ(transparent_material.getTexture(), pattern_expected);
    EXPECT_EQ(transparent_material.getTexture().getTextureColorAt(test_point_a), gfx::white());
    EXPECT_EQ(transparent_material.getTexture().getTextureColorAt(test_point_b), gfx::black());

    // Test that material properties are correctly initialized
    EXPECT_FLOAT_EQ(transparent_material.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(transparent_material.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(transparent_material.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(transparent_material.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(transparent_material.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(transparent_material.getTransparency(), transparent_transparency_expected);
    EXPECT_FLOAT_EQ(transparent_material.getRefractiveIndex(), transparent_refractive_index_expected);
}

// Tests the copy constructor
TEST(GraphicsMaterial, CopyConstructor)
{
    const gfx::ColorTexture texture_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const double transparency_expected{ 0.5 };
    const double refractive_index_expected{ 0.5 };
    const gfx::Material material_src{ texture_expected,
                                      ambient_expected,
                                      diffuse_expected,
                                      specular_expected,
                                      shininess_expected,
                                      reflectivity_expected,
                                      transparency_expected,
                                      refractive_index_expected };

    const gfx::Material material_cpy{ material_src };

    EXPECT_EQ(material_cpy.getTexture(), texture_expected);
    EXPECT_FLOAT_EQ(material_cpy.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(material_cpy.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(material_cpy.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(material_cpy.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(material_cpy.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(material_cpy.getTransparency(), transparency_expected);
    EXPECT_FLOAT_EQ(material_cpy.getRefractiveIndex(), refractive_index_expected);
}

// Tests the assignment operator
TEST(GraphicsMaterial, AssignmentOperator)
{
    const gfx::ColorTexture texture_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const double transparency_expected{ 0.5 };
    const double refractive_index_expected{ 0.5 };
    const gfx::Material material_a{ texture_expected,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected,
                                    reflectivity_expected,
                                    transparency_expected,
                                    refractive_index_expected };
    gfx::Material material_b{ };

    material_b = material_a;

    EXPECT_EQ(material_b.getTexture(), texture_expected);
    EXPECT_FLOAT_EQ(material_b.getAmbient(), ambient_expected);
    EXPECT_FLOAT_EQ(material_b.getDiffuse(), diffuse_expected);
    EXPECT_FLOAT_EQ(material_b.getSpecular(), specular_expected);
    EXPECT_FLOAT_EQ(material_b.getShininess(), shininess_expected);
    EXPECT_FLOAT_EQ(material_b.getReflectivity(), reflectivity_expected);
    EXPECT_FLOAT_EQ(material_b.getTransparency(), transparency_expected);
    EXPECT_FLOAT_EQ(material_b.getRefractiveIndex(), refractive_index_expected);
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
    const gfx::ColorTexture texture_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const double transparency_expected{ 0.5 };
    const double refractive_index_expected{ 0.5 };
    const gfx::Material material_a{ texture_expected,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected,
                                    reflectivity_expected,
                                    transparency_expected,
                                    refractive_index_expected };
    const gfx::Material material_b{ };

    EXPECT_TRUE(material_a != material_b);
}

// Tests mutator methods
TEST(GraphicsMaterial, Mutators)
{
    gfx::Material material{ };

    // setPattern (Copy Semantics)
    const gfx::StripePattern pattern_expected{ gfx::create2DScalingMatrix(5),
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
            gfx::create2DScalingMatrix(5),
            gfx::white(),
            gfx::black()
            ));
    EXPECT_EQ(material.getTexture(), pattern_expected);

    // setAmbient
    const double ambient_expected{ 0.5 };
    material.setAmbient(ambient_expected);
    EXPECT_FLOAT_EQ(material.getAmbient(), ambient_expected);

    // setDiffuse
    const double diffuse_expected{ 0.5 };
    material.setDiffuse(diffuse_expected);
    EXPECT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);

    // setSpecular
    const double specular_expected{ 0.5 };
    material.setSpecular(specular_expected);
    EXPECT_FLOAT_EQ(material.getSpecular(), specular_expected);

    // setShininess
    const double shininess_expected{ 50 };
    material.setShininess(shininess_expected);
    EXPECT_FLOAT_EQ(material.getShininess(), shininess_expected);

    // setReflectivity
    const double reflectivity_expected{ 0.5 };
    material.setReflectivity(reflectivity_expected);
    EXPECT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);

    // setTransparency
    const double transparency_expected{ 0.5 };
    material.setTransparency(transparency_expected);
    EXPECT_FLOAT_EQ(material.getTransparency(), transparency_expected);

    // setRefractiveIndex
    const double refractive_index_expected{ 0.5 };
    material.setRefractiveIndex(refractive_index_expected);
    EXPECT_FLOAT_EQ(material.getTransparency(), refractive_index_expected);
}

// Tests creating a glassy material using the factory function
TEST(GraphicsMaterial, CreateGlassyMaterial)
{
    const gfx::Material glassy_material{ gfx::createGlassyMaterial() };
    EXPECT_FLOAT_EQ(glassy_material.getTransparency(), 1);
    EXPECT_FLOAT_EQ(glassy_material.getRefractiveIndex(), 1.5);
}

#pragma clang diagnostic pop