/*--------------------------------------------------------------
* Virtual Cannon
* Ray Tracer Challenge - Chapter 1 Demo (Putting It Together)
*
* Implementation by Jacob Barber
----------------------------------------------------------------*/

#include <print>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "vector4.hpp"

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
    if (argc != 2) {
        std::println(std::cerr, "Error: Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    // Read in the projectile position data
    std::ifstream file;
    file.open(argv[1]);
    float x, y, z;
    file >> x;
    file >> y;
    file >> z;
    gfx::Vector4 initial_position = gfx::point(x, y, z);

    // Read in the projectile velocity data
    file >> x;
    file >> y;
    file >> z;
    gfx::Vector4 initial_velocity = gfx::vector(x, y, z);

    // Read in wind_speed data (if present)
    gfx::Vector4 wind_speed = gfx::vector(0.0, 0.0, 0.0);
    if (!file.eof()) {
        file >> x;
        file >> y;
        file >> z;
        wind_speed = gfx::vector(x, y, z);
    }

    // Read in gravity data (if present)
    gfx::Vector4 gravity = gfx::vector(0.0, -9.8, 0.0);
    if (!file.eof()) {
        file >> y;
        gravity = gfx::vector(0.0, y, 0.0);
    }

    // Initialize the data
    Environment env{ gravity, wind_speed };
    Projectile proj{ initial_position, initial_velocity };

    int tick_num = 0;
    while (proj.position.y() >= 0) {
        std::println("Tick {}: ({}, {}, {})",
                     tick_num,
                     proj.position.x(),
                     proj.position.y(),
                     proj.position.z());
        proj = tick(proj, env);
        ++tick_num;
    }

    return EXIT_SUCCESS;
}