#include "gtest/gtest.h"
#include "material.hpp"

#include "color.hpp"
#include "stripe_pattern.hpp"
#include "transform.hpp"

// Tests the default constructor
TEST(GraphicsMaterial, DefaultConstructor)
{
    const gfx::Material material{ };
    const gfx::Color color_expected{ 1, 1, 1 };
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const double reflectivity_expected{ 0 };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FALSE(material.hasPattern());
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
}

// Tests the color-only constructor
TEST(GraphicsMaterial, ColorConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const double reflectivity_expected{ 0 };
    const gfx::Material material{ color_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FALSE(material.hasPattern());
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
}

// Tests the pattern-only constructor
TEST(GraphicsMaterial, PatternOnlyConstructor)
{
    const gfx::Color color_expected{ 1, 1, 1 };
    const gfx::StripePattern pattern_expected{ gfx::createScalingMatrix(5),
                                               gfx::white(),
                                               gfx::black() };
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const double reflectivity_expected{ 0 };
    const gfx::Material material{ pattern_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_EQ(material.getPattern(), pattern_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
}

// Tests the Phong values list-only constructor
TEST(GraphicsMaterial, PhongValuesList)
{
    const gfx::Color color_expected{ 1, 1, 1 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const gfx::Material material{ ambient_expected,
                                  diffuse_expected,
                                  specular_expected,
                                  shininess_expected,
                                  reflectivity_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FALSE(material.hasPattern());
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
}

// Tests the no-pattern constructors
TEST(GraphicsMaterial, NoPatternConstructors)
{
    // Test the color object constructor
    const gfx::Color color_a_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const gfx::Material material_a{ color_a_expected,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected,
                                    reflectivity_expected };

    ASSERT_EQ(material_a.getColor(), color_a_expected);
    ASSERT_FLOAT_EQ(material_a.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material_a.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material_a.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material_a.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material_a.getReflectivity(), reflectivity_expected);

    // Test the float list constructor
    const double color_r{ 0.5 };
    const double color_g{ 0.5 };
    const double color_b{ 0.5 };
    const gfx::Color color_b_expected{ color_r, color_g, color_b };
    const gfx::Material material_b{ color_r,
                                    color_g,
                                    color_b,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected,
                                    reflectivity_expected };

    ASSERT_EQ(material_b.getColor(), color_b_expected);
    ASSERT_FLOAT_EQ(material_b.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material_b.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material_b.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material_b.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material_b.getReflectivity(), reflectivity_expected);
}

// Tests the no-color constructor
TEST(GraphicsMaterial, NoColorConstructor)
{
    // Test the color object constructor
    const gfx::Color color_expected{ 1, 1, 1 };
    const gfx::StripePattern pattern_expected{ gfx::createScalingMatrix(5),
                                               gfx::white(),
                                               gfx::black() };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const gfx::Material material{ pattern_expected,
                                  ambient_expected,
                                  diffuse_expected,
                                  specular_expected,
                                  shininess_expected,
                                  reflectivity_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_EQ(material.getPattern(), pattern_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
}

// Tests the copy constructor
TEST(GraphicsMaterial, CopyConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const gfx::Material material_src{ color_expected,
                                      ambient_expected,
                                      diffuse_expected,
                                      specular_expected,
                                      shininess_expected,
                                      reflectivity_expected };

    const gfx::Material material_cpy{ material_src };

    ASSERT_EQ(material_cpy.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material_cpy.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material_cpy.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material_cpy.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material_cpy.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material_cpy.getReflectivity(), reflectivity_expected);
}

// Tests the assignment operator
TEST(GraphicsMaterial, AssignmentOperator)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const gfx::Material material_a{ color_expected,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected,
                                    reflectivity_expected };
    gfx::Material material_b{ };

    material_b = material_a;

    ASSERT_EQ(material_b.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material_b.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material_b.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material_b.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material_b.getShininess(), shininess_expected);
    ASSERT_FLOAT_EQ(material_b.getReflectivity(), reflectivity_expected);
}

// Tests the equality operator
TEST(GraphicsMaterial, EqualityOperator)
{
const gfx::Material material_a{ };
const gfx::Material material_b{ };

ASSERT_TRUE(material_a == material_b);
}

// Tests the inequality operator
TEST(GraphicsMaterial, InequalityOperator)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const double reflectivity_expected{ 0.5 };
    const gfx::Material material_a{ color_expected,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected,
                                    reflectivity_expected };
    const gfx::Material material_b{ };

    ASSERT_TRUE(material_a != material_b);
}

// Tests mutator methods
TEST(GraphicsMaterial, Mutators)
{
    gfx::Material material{ };

    // setColor (Color Object)
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    material.setColor(color_expected);
    ASSERT_EQ(material.getColor(), color_expected);

    // setColor (Float List)
    material.setColor(0.5, 0.5, 0.5);
    ASSERT_EQ(material.getColor(), color_expected);

    // setPattern (Copy Semantics)
    const gfx::StripePattern pattern_expected{ gfx::createScalingMatrix(5),
                                               gfx::white(),
                                               gfx::black() };
    material.setPattern(pattern_expected);
    ASSERT_EQ(material.getPattern(), pattern_expected);

    // setPattern (Move Semantics)
    material.setPattern(std::make_unique<gfx::StripePattern>(
            gfx::createScalingMatrix(5),
            gfx::white(),
            gfx::black()
            ));
    ASSERT_EQ(material.getPattern(), pattern_expected);

    // setAmbient
    const double ambient_expected{ 0.5 };
    material.setAmbient(ambient_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);

    // setDiffuse
    const double diffuse_expected{ 0.5 };
    material.setDiffuse(diffuse_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);

    // setSpecular
    const double specular_expected{ 0.5 };
    material.setSpecular(specular_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);

    // setShininess
    const double shininess_expected{ 50 };
    material.setShininess(shininess_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);

    // setReflectivity
    const double reflectivity_expected{ 0.5 };
    material.setReflectivity(reflectivity_expected);
    ASSERT_FLOAT_EQ(material.getReflectivity(), reflectivity_expected);
}