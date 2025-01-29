#include "gtest/gtest.h"
#include "material.hpp"

#include "color.hpp"

// Tests the default constructor
TEST(GraphicsMaterial, DefaultConstructor)
{
    const gfx::Material material{ };
    const gfx::Color color_expected{ 1, 1, 1 };
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
}

// Tests the standard constructor (color object & double list)
TEST(GraphicsMaterial, StandardConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const gfx::Material material{ color_expected,
                                  ambient_expected,
                                  diffuse_expected,
                                  specular_expected,
                                  shininess_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
}

// Tests the standard constructor (double list)
TEST(GraphicsMaterial, StandardFloatListConstructor)
{
    const float color_r{ 0.5 };
    const float color_g{ 0.5 };
    const float color_b{ 0.5 };
    const gfx::Color color_expected{ color_r, color_g, color_b };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const gfx::Material material{ color_r,
                                  color_g,
                                  color_b,
                                  ambient_expected,
                                  diffuse_expected,
                                  specular_expected,
                                  shininess_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
}

// Tests the color constructor
TEST(GraphicsMaterial, ColorConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.1 };
    const double diffuse_expected{ 0.9 };
    const double specular_expected{ 0.9 };
    const double shininess_expected{ 200 };
    const gfx::Material material{ color_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
}

// Tests the attribute list constructor
TEST(GraphicsMaterial, AttributeList)
{
    const gfx::Color color_expected{ 1, 1, 1 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const gfx::Material material{ ambient_expected,
                                  diffuse_expected,
                                  specular_expected,
                                  shininess_expected };

    ASSERT_EQ(material.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
}

// Tests the copy constructor
TEST(GraphicsMaterial, CopyConstructor)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };
    const gfx::Material material_src{ color_expected,
                                      ambient_expected,
                                      diffuse_expected,
                                      specular_expected,
                                      shininess_expected };

    const gfx::Material material_cpy{ material_src };

    ASSERT_EQ(material_cpy.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material_cpy.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material_cpy.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material_cpy.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material_cpy.getShininess(), shininess_expected);
}

// Tests the assignment operator
TEST(GraphicsMaterial, AssignmentOperator)
{
    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    const double ambient_expected{ 0.5 };
    const double diffuse_expected{ 0.5 };
    const double specular_expected{ 0.5 };
    const double shininess_expected{ 50 };

    const gfx::Material material_a{ color_expected,
                                      ambient_expected,
                                      diffuse_expected,
                                      specular_expected,
                                      shininess_expected };
    gfx::Material material_b{ };

    material_b = material_a;

    ASSERT_EQ(material_b.getColor(), color_expected);
    ASSERT_FLOAT_EQ(material_b.getAmbient(), ambient_expected);
    ASSERT_FLOAT_EQ(material_b.getDiffuse(), diffuse_expected);
    ASSERT_FLOAT_EQ(material_b.getSpecular(), specular_expected);
    ASSERT_FLOAT_EQ(material_b.getShininess(), shininess_expected);
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

    const gfx::Material material_a{ color_expected,
                                    ambient_expected,
                                    diffuse_expected,
                                    specular_expected,
                                    shininess_expected };
    const gfx::Material material_b{ };

    ASSERT_TRUE(material_a != material_b);
}

// Tests mutator methods
TEST(GraphicsMaterial, Mutators)
{
    gfx::Material material{ };

    const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
    material.setColor(color_expected);
    ASSERT_EQ(material.getColor(), color_expected);

    const double ambient_expected{ 0.5 };
    material.setAmbient(ambient_expected);
    ASSERT_FLOAT_EQ(material.getAmbient(), ambient_expected);

    const double diffuse_expected{ 0.5 };
    material.setDiffuse(diffuse_expected);
    ASSERT_FLOAT_EQ(material.getDiffuse(), diffuse_expected);

    const double specular_expected{ 0.5 };
    material.setSpecular(specular_expected);
    ASSERT_FLOAT_EQ(material.getSpecular(), specular_expected);

    const double shininess_expected{ 50 };
    material.setShininess(shininess_expected);
    ASSERT_FLOAT_EQ(material.getShininess(), shininess_expected);
}