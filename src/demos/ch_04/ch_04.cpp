/*--------------------------------------------------------------
* Clock Face Point Plotter
* Ray Tracer Challenge - Chapter 4 Demo (Putting It Together)
*
* Implementation by Jacob Barber
----------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "canvas.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"
#include "transform.hpp"
#include "color.hpp"

constexpr size_t CANVAS_DIMENSION{ 501 };
constexpr float RADIUS_SCALE_FACTOR{ 0.375 };
constexpr float RADIUS{ CANVAS_DIMENSION * RADIUS_SCALE_FACTOR };

int main(int argc, char** argv)
{
    // Validate number of arguments
    if (argc != 2) {
        std::println(std::cerr, "Error: Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    // Create a square canvas
    const gfx::Canvas canvas{ CANVAS_DIMENSION, CANVAS_DIMENSION };

    // Define the transformation matrices
    const gfx::Matrix4 center_translation_matrix{ gfx::createTranslationMatrix(std::round(CANVAS_DIMENSION / 2),
                                                                               std::round(CANVAS_DIMENSION / 2),
                                                                               0.0) };
    const gfx::Matrix4 radius_scaling_matrix{ gfx::createScalingMatrix(RADIUS) };
    gfx::Matrix4 clock_rotation_matrix{ gfx::createZRotationMatrix(-M_PI / 6) };

    // Draw the clock face to the canvas
    gfx::Color white{ 1, 1, 1 };
    gfx::Vector4 current_clock_point{ gfx::createPoint(0, 1, 0) };
    for (int i = 0; i < 12; ++i) {
        const gfx::Vector4 canvas_draw_pos{ (center_translation_matrix * radius_scaling_matrix) * current_clock_point };
        size_t x_pos = std::round(canvas_draw_pos.x());
        size_t y_pos = CANVAS_DIMENSION - std::round(canvas_draw_pos.y());
        canvas[x_pos, y_pos] = white;
        current_clock_point *= clock_rotation_matrix;
    }

    // Export data to PPM file
    const std::string_view output_file_path = argv[1];
    std::ofstream out_file{ output_file_path, std::ios_base::trunc};
    out_file << gfx::exportAsPPM(canvas);

    return EXIT_SUCCESS;
}