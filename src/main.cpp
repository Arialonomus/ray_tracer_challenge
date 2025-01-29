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

#include "parse.hpp"
#include "canvas.hpp"
#include "rendering_functions.hpp"

int main(int argc, char** argv)
{
    // Validate number of arguments
    if (argc != 3) {
        std::println(std::cerr, "Error: Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    // Read in scene data
    std::string_view input_file_path{ argv[1] };
    std::ifstream input_file{ input_file_path };
    json scene_data = json::parse(input_file);
    Scene scene{ data::parseSceneData(scene_data) };

    // Render the scene to a canvas
    rt::Canvas image{ rt::render(scene.world, scene.camera) };

    // Export data to PPM file
    const std::string_view output_file_path{ argv[2] };
    std::ofstream out_file{ output_file_path, std::ios_base::trunc};
    out_file << rt::exportAsPPM(image);

    return EXIT_SUCCESS;
}