/*--------------------------------------------------------------
* Sphere Silhouette Renderer
* Ray Tracer Challenge - Chapter 5 Demo (Putting It Together)
*
* Implementation by Jacob Barber
----------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "canvas.hpp"

constexpr size_t CANVAS_DIMENSION{ 500 };

int main(int argc, char** argv)
{
    // Validate number of arguments
    if (argc != 2) {
        std::println(std::cerr, "Error: Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    // Create a square canvas
    const gfx::Canvas canvas{ CANVAS_DIMENSION, CANVAS_DIMENSION };

    // Export data to PPM file
    const std::string_view output_file_path = argv[1];
    std::ofstream out_file{ output_file_path, std::ios_base::trunc};
    out_file << gfx::exportAsPPM(canvas);

    return EXIT_SUCCESS;
}