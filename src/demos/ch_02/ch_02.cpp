/*--------------------------------------------------------------
* Virtual Cannon Plotter
* Ray Tracer Challenge - Chapter 2 Demo (Putting It Together)
*
* Implementation by Jacob Barber
----------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "vector4.hpp"
#include "canvas.hpp"

constexpr float SCALING_FACTOR{ 11.25 };    // Scaling factor given in the book to generate a better image

struct Projectile
{
    gfx::Vector4 position;
    gfx::Vector4 velocity;
};

struct Environment
{
    gfx::Vector4 gravity;
    gfx::Vector4 wind_speed;
};

Projectile tick(Projectile proj, Environment env)
{
    return Projectile{ proj.position + proj.velocity, proj.velocity + env.gravity + env.wind_speed };
}

int main(int argc, char** argv)
{
    // Validate number of arguments
    if (argc != 3) {
        std::println(std::cerr, "Error: Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    // Open the file
    std::ifstream file;
    file.open(argv[1]);

    // Read in canvas size
    size_t width, height;
    file >> width;
    file >> height;

    // Read in the projectile position data
    float input_x, input_y, input_z;
    file >> input_x;
    file >> input_y;
    file >> input_z;
    gfx::Vector4 initial_position = gfx::point(input_x, input_y, input_z);

    // Read in the projectile velocity data
    file >> input_x;
    file >> input_y;
    file >> input_z;
    gfx::Vector4 initial_velocity = gfx::vector(input_x, input_y, input_z);

    // Read in wind_speed data (if present)
    gfx::Vector4 wind_speed = gfx::vector(0.0, 0.0, 0.0);
    if (!file.eof()) {
        file >> input_x;
        file >> input_y;
        file >> input_z;
        wind_speed = gfx::vector(input_x, input_y, input_z);
    }

    // Read in gravity data (if present)
    gfx::Vector4 gravity = gfx::vector(0.0, -9.8, 0.0);
    if (!file.eof()) {
        file >> input_y;
        gravity = gfx::vector(0.0, input_y, 0.0);
    }

    // Create the canvas
    const gfx::Canvas canvas{ width, height };

    // Initialize the data
    Environment env{ gravity, wind_speed };
    Projectile proj{ initial_position, gfx::normalize(initial_velocity) * SCALING_FACTOR };

    // Plot the trajectory on the canvas
    const gfx::Color red{1.0, 0.0, 0.0};
    while (proj.position.y() >= 0) {
        size_t x_pos = std::round(proj.position.x());
        size_t y_pos = height - std::round(proj.position.y());
        canvas[x_pos, y_pos] = red;
        proj = tick(proj, env);
    }

    // Export data to PPM file
    std::ofstream out_file{ argv[2], std::ios_base::trunc};
    out_file << gfx::exportAsPPM(canvas);

    return EXIT_SUCCESS;
}