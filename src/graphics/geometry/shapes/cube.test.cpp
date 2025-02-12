#include "gtest/gtest.h"
#include "cube.hpp"

#include <cmath>

#include "matrix4.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "ray.hpp"

// Tests the default constructor
TEST(GraphicsCube, DefaultConstructor)
{
const gfx::Cube cube{ };
const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };
const gfx::Material material_expected{ };

ASSERT_EQ(cube.getTransform(), transform_expected);
ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the standard constructor
TEST(GraphicsCube, StandardConstructor)
{
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
const gfx::Cube cube{ gfx::createScalingMatrix(5), material_expected };
const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };

ASSERT_EQ(cube.getTransform(), transform_expected);
ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the standard constructor (with default material)
TEST(GraphicsCube, StandardConstructorDefaultMaterial)
{
const gfx::Cube cube{ gfx::createScalingMatrix(5) };
const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
const gfx::Material material_expected{ };

ASSERT_EQ(cube.getTransform(), transform_expected);
ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the standard constructor (with default transform)
TEST(GraphicsCube, StandardConstructorDefaultTransform)
{
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
const gfx::Cube cube{ material_expected };
const gfx::Matrix4 transform_expected{ gfx::createIdentityMatrix() };

ASSERT_EQ(cube.getTransform(), transform_expected);
ASSERT_EQ(cube.getMaterial(), material_expected);
}

// Tests the copy constructor
TEST(GraphicsCube, CopyConstructor)
{
const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
const gfx::Cube cube_src{ transform_expected, material_expected };
const gfx::Cube cube_cpy{ cube_src };

ASSERT_EQ(cube_cpy.getTransform(), transform_expected);
ASSERT_EQ(cube_cpy.getMaterial(), material_expected);
}

// Tests the assignment operator
TEST(GraphicsCube, AssignmentOperator)
{

const gfx::Matrix4 transform_expected{ gfx::createScalingMatrix(5) };
const gfx::Color color_expected{ 0.5, 0.5, 0.5 };
const gfx::Material material_expected{ color_expected, 0.5, 0.5, 0.5, 50, 0.5 };
const gfx::Cube cube_a{ transform_expected, material_expected };
gfx::Cube cube_b{ };

cube_b = cube_a;

ASSERT_EQ(cube_b.getTransform(), transform_expected);
ASSERT_EQ(cube_b.getMaterial(), material_expected);
}

// Tests the equality operator
TEST(GraphicsCube, EqualityOperator)
{
const gfx::Cube cube_a{ gfx::createScalingMatrix(5) };
const gfx::Cube cube_b{ gfx::createScalingMatrix(5) };

ASSERT_TRUE(cube_a == cube_b);
}

// Tests the inequality operator
TEST(GraphicsCube, InequalityOperator)
{
const gfx::Cube cube_a{ gfx::createScalingMatrix(5) };
const gfx::Cube cube_b{ };

ASSERT_TRUE(cube_a != cube_b);
}