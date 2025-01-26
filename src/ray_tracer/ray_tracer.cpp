/*--------------------------------------------------------------
* Ray Tracer
*
* A CPU-based ray tracer program based on the spec outlined in
* "The Ray Tracer Challenge" by Jamis Buck
*
* Implementation by Jacob Barber
----------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <print>
#include <optional>

#include "canvas.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "vector4.hpp"
#include "ray.hpp"

constexpr size_t CANVAS_DIMENSION{ 500 };
constexpr float BACKDROP_Z{ 10 };
constexpr float BACKDROP_SIZE{ 7 };
constexpr float PIXEL_SIZE{ BACKDROP_SIZE / CANVAS_DIMENSION };
constexpr float WALL_COORDINATE_LIMIT{ BACKDROP_SIZE / 2 };

int main(int argc, char** argv)
{
    // Validate number of arguments
    if (argc != 2) {
        std::println(std::cerr, "Error: Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    // Create a square canvas
    const gfx::Canvas canvas{ CANVAS_DIMENSION, CANVAS_DIMENSION };

    // Initialize the scene
    const gfx::Sphere shape{ };
    const gfx::Vector4 ray_origin{ gfx::createPoint(0, 0, -5) };
    const gfx::Color red{ 1, 0, 0 };

    // Cast a ray for every canvas pixel from the origin to the backdrop and check for intersections
    for (int y = 0; y < CANVAS_DIMENSION; ++y) {
        float world_y{ WALL_COORDINATE_LIMIT - PIXEL_SIZE * y };
        for (int x = 0; x < CANVAS_DIMENSION; ++x) {
            float world_x{ -WALL_COORDINATE_LIMIT + PIXEL_SIZE * x };

            // Create a ray targeting the world-space pixel on the backdrop
            const gfx::Vector4 ray_target_pos{ gfx::createPoint(world_x, world_y, BACKDROP_Z) };
            const gfx::Ray ray{ ray_origin, gfx::normalize(ray_target_pos - ray_origin) };

            // Cast the ray and check for an intersection with the sphere
            auto possible_hit{ gfx::getHit(ray.getIntersections(shape)) };
            if (possible_hit) {
                canvas[x, y] = red;
            }
        }
    }

    // Export data to PPM file
    const std::string_view output_file_path = argv[1];
    std::ofstream out_file{ output_file_path, std::ios_base::trunc};
    out_file << gfx::exportAsPPM(canvas);

    return EXIT_SUCCESS;
}