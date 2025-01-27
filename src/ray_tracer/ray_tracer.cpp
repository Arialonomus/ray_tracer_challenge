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
#include "material.hpp"
#include "light.hpp"
#include "shading_functions.hpp"

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
    gfx::Material material{ 1, 0.2, 1 };
    const gfx::Sphere shape{ material };

    const gfx::PointLight light{ gfx::Color{ 1, 1, 1 },
                                 gfx::createPoint(-10, 10, -10) };
    const gfx::Vector4 viewpoint_origin{ gfx::createPoint(0, 0, -5) };

    // Cast a ray for every canvas pixel from the origin to the backdrop and check for intersections
    for (int y = 0; y < CANVAS_DIMENSION; ++y) {
        float world_y{ WALL_COORDINATE_LIMIT - PIXEL_SIZE * y };
        for (int x = 0; x < CANVAS_DIMENSION; ++x) {
            float world_x{ -WALL_COORDINATE_LIMIT + PIXEL_SIZE * x };

            // Create a ray targeting the world-space pixel on the backdrop
            const gfx::Vector4 ray_target_pos{ gfx::createPoint(world_x, world_y, BACKDROP_Z) };
            const gfx::Ray ray{ viewpoint_origin, gfx::normalize(ray_target_pos - viewpoint_origin) };

            // Cast the ray and check for an intersection with the sphere
            auto possible_hit{ gfx::getHit(ray.getIntersections(shape)) };

            // Hit found, draw the pixel to the canvas
            if (possible_hit) {
                // Extract the intersection data and calculate the position on the surface in world space
                const gfx::Intersection intersection = possible_hit.value();
                const gfx::Sphere object = intersection.getObject();
                const gfx::Vector4 surface_position{ ray.position(intersection.getT()) };

                // Calculate the normal vector in world space
                const gfx::Vector4 normal_vector{ object.getSurfaceNormal(surface_position) };

                // Set the view vector and shade the pixel
                const gfx::Vector4 view_vector{ -normalize(ray.getDirection()) };
                canvas[x, y] = gfx::calculateSurfaceColor(object.getMaterial(),
                                                          light,
                                                          surface_position,
                                                          normal_vector,
                                                          view_vector);
            }
        }
    }

    // Export data to PPM file
    const std::string_view output_file_path = argv[1];
    std::ofstream out_file{ output_file_path, std::ios_base::trunc};
    out_file << gfx::exportAsPPM(canvas);

    return EXIT_SUCCESS;
}