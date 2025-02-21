#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

#include "gtest/gtest.h"
#include "bounding_box.hpp"

#include <limits>
#include <vector>

// Tests the default constructor
TEST(GraphicsBoundingBox, DefaultConstructor)
{
    const gfx::BoundingBox bounding_box{ };

    EXPECT_EQ(bounding_box.getMinX(), std::numeric_limits<double>::infinity());
    EXPECT_EQ(bounding_box.getMinY(), std::numeric_limits<double>::infinity());
    EXPECT_EQ(bounding_box.getMinZ(), std::numeric_limits<double>::infinity());
    EXPECT_EQ(bounding_box.getMaxX(), -std::numeric_limits<double>::infinity());
    EXPECT_EQ(bounding_box.getMaxY(), -std::numeric_limits<double>::infinity());
    EXPECT_EQ(bounding_box.getMaxZ(), -std::numeric_limits<double>::infinity());
}

// Tests the float list constructor
TEST(GraphicsBoundingBox, FloatListConstructor)
{
    const gfx::BoundingBox bounding_box{ -1, -2, -3,
                                         3, 2, 1};

    const gfx::Vector4 min_extent_expected{ gfx::createPoint(-1, -2, -3) };
    const gfx::Vector4 max_extent_expected{ gfx::createPoint(3, 2, 1) };

    EXPECT_EQ(bounding_box.getMinExtentPoint(), min_extent_expected);
    EXPECT_EQ(bounding_box.getMaxExtentPoint(), max_extent_expected);
}

// Tests the extent coordinate constructor
TEST(GraphicsBoundingBox, ExtentCoordinateConstructor)
{
    const gfx::Vector4 min_extent_expected{ gfx::createPoint(-1, -2, -3) };
    const gfx::Vector4 max_extent_expected{ gfx::createPoint(3, 2, 1) };
    const gfx::BoundingBox bounding_box{ min_extent_expected,
                                         max_extent_expected };

    EXPECT_EQ(bounding_box.getMinExtentPoint(), min_extent_expected);
    EXPECT_EQ(bounding_box.getMaxExtentPoint(), max_extent_expected);
}

// Tests the copy constructor
TEST(GraphicsBoundingBox, CopyConstructor)
{
    const gfx::Vector4 min_extent_expected{ gfx::createPoint(-1, -2, -3) };
    const gfx::Vector4 max_extent_expected{ gfx::createPoint(3, 2, 1) };
    const gfx::BoundingBox bounding_box_src{ min_extent_expected,
                                             max_extent_expected };
    const gfx::BoundingBox bounding_box_cpy{ bounding_box_src };

    EXPECT_EQ(bounding_box_cpy.getMinExtentPoint(), min_extent_expected);
    EXPECT_EQ(bounding_box_cpy.getMaxExtentPoint(), max_extent_expected);
}

// Tests the assignment operator
TEST(GraphicsBoundingBox, AssignmentOperator)
{
    const gfx::Vector4 min_extent_expected{ gfx::createPoint(-1, -2, -3) };
    const gfx::Vector4 max_extent_expected{ gfx::createPoint(3, 2, 1) };
    const gfx::BoundingBox bounding_box_a{ min_extent_expected,
                                           max_extent_expected };
    gfx::BoundingBox bounding_box_b{ };

    bounding_box_b = bounding_box_a;

    EXPECT_EQ(bounding_box_b.getMinExtentPoint(), min_extent_expected);
    EXPECT_EQ(bounding_box_b.getMaxExtentPoint(), max_extent_expected);
}

// Tests the equality operator
TEST(GraphicsBoundingBox, EqualityOperator)
{
    const gfx::BoundingBox bounding_box_a{ -1, -2, -3,
                                           3, 2, 1};
    const gfx::BoundingBox bounding_box_b{ bounding_box_a };

    ASSERT_TRUE(bounding_box_a == bounding_box_b);
}

// Tests the inequality operator
TEST(GraphicsBoundingBox, InequalityOperator)
{
    const gfx::BoundingBox bounding_box_a{ -1, -2, -3,
                                           3, 2, 1};
    const gfx::BoundingBox bounding_box_b{ };

    ASSERT_TRUE(bounding_box_a != bounding_box_b);
}

// Tests the mutator methods
TEST(GraphicsBoundingBox, Mutators)
{
    gfx::BoundingBox bounding_box{ };

    // Test setting minimum and maximum extents by individual values
    bounding_box.setMinX(-10);
    bounding_box.setMinY(-5);
    bounding_box.setMinZ(-1.23);

    const gfx::Vector4 min_extent_point_individual_value_expected{ gfx::createPoint(-10, -5, -1.23) };
    const gfx::Vector4 min_extent_point_individual_value_actual{ bounding_box.getMinExtentPoint() };
    EXPECT_EQ(min_extent_point_individual_value_actual, min_extent_point_individual_value_expected);

    bounding_box.setMaxX(4);
    bounding_box.setMaxY(5.125);
    bounding_box.setMaxZ(0);

    const gfx::Vector4 max_extent_point_individual_value_expected{ gfx::createPoint(4, 5.125, 0) };
    const gfx::Vector4 max_extent_point_individual_value_actual{ bounding_box.getMaxExtentPoint() };
    EXPECT_EQ(max_extent_point_individual_value_actual, max_extent_point_individual_value_expected);

    // Test setting minium and maximum extents at once using float lists
    bounding_box.setMinExtent(-3, -2, -1);

    const gfx::Vector4 min_extent_point_float_list_expected{ gfx::createPoint(-3, -2, -1) };
    const gfx::Vector4 min_extent_point_float_list_actual{ bounding_box.getMinExtentPoint() };
    EXPECT_EQ(min_extent_point_float_list_actual, min_extent_point_float_list_expected);

    bounding_box.setMaxExtent(1, 2, 3);

    const gfx::Vector4 max_extent_point_float_list_expected{ gfx::createPoint(1, 2, 3) };
    const gfx::Vector4 max_extent_point_float_list_actual{ bounding_box.getMaxExtentPoint() };
    EXPECT_EQ(max_extent_point_float_list_actual, max_extent_point_float_list_expected);

    // Test setting minimum and maximum extents at once using point coordinates
    const gfx::Vector4 min_extent_coordinate_expected{ gfx::createPoint(-100, -150, -200) };
    bounding_box.setMinExtent(min_extent_coordinate_expected);

    const gfx::Vector4 min_extent_coordinate_actual{ bounding_box.getMinExtentPoint() };
    EXPECT_EQ(min_extent_coordinate_actual, min_extent_coordinate_expected);

    const gfx::Vector4 max_extent_coordinate_expected{ gfx::createPoint(8, 9, 10) };
    bounding_box.setMaxExtent(max_extent_coordinate_expected);

    const gfx::Vector4 max_extent_coordinate_actual{ bounding_box.getMaxExtentPoint() };
    EXPECT_EQ(max_extent_coordinate_actual, max_extent_coordinate_expected);
}

// Tests adding points to an empty bounding box
TEST(GraphicsBoundingBox, AddPoints)
{
    gfx::BoundingBox bounding_box{ };

    const gfx::Vector4 point_a{ gfx::createPoint(-5, 2, 0) };
    const gfx::Vector4 point_b{ gfx::createPoint(7, 0, -3) };

    bounding_box.addPoint(point_a);
    bounding_box.addPoint(point_b);

    const gfx::Vector4 min_extent_expected{ gfx::createPoint(-5, 0, -3) };
    const gfx::Vector4 min_extent_actual{ bounding_box.getMinExtentPoint() };
    EXPECT_EQ(min_extent_actual, min_extent_expected);

    const gfx::Vector4 max_extent_expected{ gfx::createPoint(7, 2, 0) };
    const gfx::Vector4 max_extent_actual{ bounding_box.getMaxExtentPoint() };
    EXPECT_EQ(max_extent_actual, max_extent_expected);
}

// Tests merging a bounding box into another
TEST(GraphicsBoundingBox, MergeBoxes)
{
    gfx::BoundingBox bounding_box_a{ -5, -2, 0,
                                     7, 4, 4 };
    const gfx::BoundingBox bounding_box_b{ 8, -7, -2,
                                           14, 2, 8 };

    bounding_box_a.mergeWithBox(bounding_box_b);

    const gfx::Vector4 min_extent_expected{ gfx::createPoint(-5, -7, -2) };
    const gfx::Vector4 min_extent_actual{ bounding_box_a.getMinExtentPoint() };
    EXPECT_EQ(min_extent_actual, min_extent_expected);

    const gfx::Vector4 max_extent_expected{ gfx::createPoint(14, 4, 8) };
    const gfx::Vector4 max_extent_actual{ bounding_box_a.getMaxExtentPoint() };
    EXPECT_EQ(max_extent_actual, max_extent_expected);
}

// Tests checking if a point is contained within the extents of a bounding box
TEST(GraphicsBoundingBox, ContainsPoint)
{
    const gfx::BoundingBox bounding_box{ 5, -2, 0,
                                         11, 4, 7 };

    std::vector<std::pair<gfx::Vector4, bool>> test_cases_input_expected{
        { gfx::createPoint(5, -2, 0), true },
        { gfx::createPoint(11, 4, 7), true },
        { gfx::createPoint(8, 1, 3), true },
        { gfx::createPoint(3, 0, 3), false },
        { gfx::createPoint(8, -4, 3), false },
        { gfx::createPoint(8, 1, -1), false },
        { gfx::createPoint(13, 1, 3), false },
        { gfx::createPoint(8, 5, 3), false },
        { gfx::createPoint(8, 1, 8), false }
    };

    for (const auto test_case : test_cases_input_expected) {
        const auto input_point{ test_case.first };
        const bool result_expected{ test_case.second };

        const bool result_actual{ bounding_box.containsPoint(input_point) };
        EXPECT_EQ(result_actual, result_expected);
    }
}

#pragma clang diagnostic pop