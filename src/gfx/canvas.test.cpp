#include "gtest/gtest.h"

#include "canvas.hpp"
#include "color.hpp"

#include <string>
#include <sstream>

// Tests the standard constructor (initialized to black)
TEST(GraphicsCanvas, Constructor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Canvas canvas{ width, height };

    ASSERT_EQ(canvas.width(), width);
    ASSERT_EQ(canvas.height(), height);

    const gfx::Color black{ 0.0,0.0,0.0 };

    for (int col = 0; col < width; ++col)
        for (int row = 0; row < height; ++row) {
            gfx::Color pixel = canvas[col, row];
            ASSERT_TRUE(pixel == black);
        }
}

// Tests initializing the canvas to a specific color
TEST(GraphicsCanvas, ConstructorInitializedColor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Color red{ 1.0,0.0,0.0 };

    const gfx::Canvas canvas{ width, height, red };

    ASSERT_EQ(canvas.width(), width);
    ASSERT_EQ(canvas.height(), height);

    for (int col = 0; col < width; ++col)
        for (int row = 0; row < height; ++row) {
            gfx::Color pixel = canvas[col, row];
            ASSERT_TRUE(pixel == red);
        }
}

// Tests writing a pixel at a given coordinate
TEST(GraphicsCanvas, WritePixelColor)
{
    constexpr size_t width = 10;
    constexpr size_t height = 20;
    const gfx::Canvas canvas{ width, height };
    const gfx::Color red{ 1.0,0.0,0.0 };

    canvas[2, 3] = red;
    const gfx::Color test_pixel = canvas[2, 3];
    ASSERT_TRUE(test_pixel == red);
}

// Tests exporting a small canvas (no line wrapping) to the PPM format
TEST(GraphicsCanvas, ExportPPMSmallCanvas)
{
    constexpr size_t width = 5;
    constexpr size_t height = 3;
    const gfx::Canvas canvas{ width, height };

    // Set the test colors
    canvas[0, 0] = gfx::Color{ 1.5, 0, 0 };
    canvas[2, 1] = gfx::Color{ 0, 0.5, 0 };
    canvas[4, 2] = gfx::Color{ -0.5, 0, 1 };

    const std::string ppm_string = gfx::exportAsPPM(canvas);
    std::istringstream ppm_stream{ ppm_string };

    // Test that the header is correctly output
    constexpr std::string_view exp_header_identifier = "P3";
    constexpr std::string_view exp_header_dimensions = "5 3";
    constexpr std::string_view exp_header_color_max = "255";

    std::string act_header_identifier {};
    std::getline(ppm_stream, act_header_identifier);
    EXPECT_TRUE(act_header_identifier == exp_header_identifier);

    std::string act_header_dimensions {};
    std::getline(ppm_stream, act_header_dimensions);
    EXPECT_TRUE(act_header_dimensions == exp_header_dimensions);

    std::string act_header_color_max {};
    std::getline(ppm_stream, act_header_color_max);
    EXPECT_TRUE(act_header_color_max == exp_header_color_max);

    // Test the color data is correctly output
    constexpr std::string_view exp_row_4 = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
    constexpr std::string_view exp_row_5 = "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0";
    constexpr std::string_view exp_row_6 = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255";

    std::string act_row_4 {};
    std::getline(ppm_stream, act_row_4);
    EXPECT_TRUE(act_row_4 == exp_row_4);

    std::string act_row_5 {};
    std::getline(ppm_stream, act_row_5);
    EXPECT_TRUE(act_row_5 == exp_row_5);

    std::string act_row_6 {};
    std::getline(ppm_stream, act_row_6);
    EXPECT_TRUE(act_row_6 == exp_row_6);

    // Ensure that file ends in a newline
    EXPECT_TRUE(ppm_string.at(ppm_string.length() - 1) == '\n');
}

// Tests exporting a larger canvas (with line wrapping) to the PPM format
TEST(GraphicsCanvas, ExportPPMLargerCanvas)
{
    constexpr size_t width = 10;
    constexpr size_t height = 2;
    const gfx::Color initial_color{ 1, 0.8, 0.6 };

    const gfx::Canvas canvas{ width, height, initial_color };

    const std::string ppm_string = gfx::exportAsPPM(canvas);
    std::istringstream ppm_stream{ ppm_string };

    // Test that the header is correctly output
    constexpr std::string_view exp_header_identifier = "P3";
    constexpr std::string_view exp_header_dimensions = "10 2";
    constexpr std::string_view exp_header_color_max = "255";

    std::string act_header_identifier {};
    std::getline(ppm_stream, act_header_identifier);
    EXPECT_TRUE(act_header_identifier == exp_header_identifier);

    std::string act_header_dimensions {};
    std::getline(ppm_stream, act_header_dimensions);
    EXPECT_TRUE(act_header_dimensions == exp_header_dimensions);

    std::string act_header_color_max {};
    std::getline(ppm_stream, act_header_color_max);
    EXPECT_TRUE(act_header_color_max == exp_header_color_max);

    // Test the color data is correctly output
    constexpr std::string_view exp_row_4 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204";
    constexpr std::string_view exp_row_5 = "153 255 204 153 255 204 153 255 204 153 255 204 153";
    constexpr std::string_view exp_row_6 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204";
    constexpr std::string_view exp_row_7 = "153 255 204 153 255 204 153 255 204 153 255 204 153";

    std::string act_row_4 {};
    std::getline(ppm_stream, act_row_4);
    EXPECT_TRUE(act_row_4 == exp_row_4);

    std::string act_row_5 {};
    std::getline(ppm_stream, act_row_5);
    EXPECT_TRUE(act_row_5 == exp_row_5);

    std::string act_row_6 {};
    std::getline(ppm_stream, act_row_6);
    EXPECT_TRUE(act_row_6 == exp_row_6);

    std::string act_row_7 {};
    std::getline(ppm_stream, act_row_7);
    EXPECT_TRUE(act_row_7 == exp_row_7);

    // Ensure that file ends in a newline
    EXPECT_TRUE(ppm_string.at(ppm_string.length() - 1) == '\n');
}
