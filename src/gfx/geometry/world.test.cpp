#include "gtest/gtest.h"
#include "world.hpp"

#include <vector>

#include "light.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "intersection.hpp"

// Tests the default constructor
TEST(GraphicsWorld, DefaultConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 1, 1, 1 },
                                    gfx::createPoint(-10, 10, -10) };
    const gfx::World world{ };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_TRUE(world.getObjectList().empty());
}

// Tests the point light constructor
TEST(GraphicsWorld, PointLightConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 0.5, 0.5, 0.5 },
                                           gfx::createPoint(-5, 5, -5) };
    const gfx::World world{ light_source_expected };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_TRUE(world.getObjectList().empty());
}

// Tests the object list constructor
TEST(GraphicsWorld, ObjectListConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 1, 1, 1 },
                                           gfx::createPoint(-10, 10, -10) };
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ };
    const std::vector<std::reference_wrapper<gfx::Sphere>> object_list{ sphere_a, sphere_b };
    const gfx::World world{ object_list };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_EQ(world.getObjectList().size(), 2);
    ASSERT_EQ(&world.getObjectList().at(0).get(), &sphere_a);
    ASSERT_EQ(&world.getObjectList().at(1).get(), &sphere_b);
}


// Tests the standard constructor
TEST(GraphicsWorld, StandardConstructor)
{
    const gfx::PointLight light_source_expected{ gfx::Color{ 0.5, 0.5, 0.5 },
                                                 gfx::createPoint(-5, 5, -5) };
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ };
    const std::vector<std::reference_wrapper<gfx::Sphere>> object_list{ sphere_a, sphere_b };
    const gfx::World world{ light_source_expected, object_list };

    ASSERT_EQ(world.getLightSource().intensity, light_source_expected.intensity);
    ASSERT_EQ(world.getLightSource().position, light_source_expected.position);
    ASSERT_EQ(world.getObjectList().size(), 2);
    ASSERT_EQ(&world.getObjectList().at(0).get(), &sphere_a);
    ASSERT_EQ(&world.getObjectList().at(1).get(), &sphere_b);
}

// Tests calculating world intersections
TEST(GraphicsWorld, WorldIntersections)
{
    gfx::Sphere sphere_a{ };
    gfx::Sphere sphere_b{ gfx::createScalingMatrix(0.5) };
    const std::vector<std::reference_wrapper<gfx::Sphere>> object_list{ sphere_a, sphere_b };
    const gfx::World world{ object_list };
    const gfx::Ray ray{ 0, 0, -5,
                        0, 0, 1 };

    const std::vector<gfx::Intersection> world_intersections{ world.getIntersections(ray) };

    EXPECT_EQ(world_intersections.size(), 4);
    EXPECT_FLOAT_EQ(world_intersections.at(0).getT(), 4);
    EXPECT_FLOAT_EQ(world_intersections.at(1).getT(), 4.5);
    EXPECT_FLOAT_EQ(world_intersections.at(2).getT(), 5.5);
    EXPECT_FLOAT_EQ(world_intersections.at(3).getT(), 6);
}
