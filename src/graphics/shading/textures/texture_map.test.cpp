#include "gtest/gtest.h"
#include "texture_map.hpp"

// Test using the projection mapping to map object space coordinates to texture space
TEST(GraphicsTextureMap, ProjectionMap)
{
    const gfx::Vector4 object_coordinate_a{ gfx::createPoint(5, 2, 1) };
    const gfx::Vector3 texture_coordinate_a_expected{ gfx::create2DPoint(5, 1) };
    const gfx::Vector3 texture_coordinate_a_actual{ gfx::ProjectionMap(object_coordinate_a) };
    EXPECT_EQ(texture_coordinate_a_actual, texture_coordinate_a_expected);

    const gfx::Vector4 object_coordinate_b{ gfx::createPoint(0, -10, 0) };
    const gfx::Vector3 texture_coordinate_b_expected{ gfx::create2DPoint(0, 0) };
    const gfx::Vector3 texture_coordinate_b_actual{ gfx::ProjectionMap(object_coordinate_b) };
    EXPECT_EQ(texture_coordinate_b_actual, texture_coordinate_b_expected);
}