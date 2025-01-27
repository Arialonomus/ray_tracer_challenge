#include "canvas.hpp"

#include <sstream>
#include <array>

#include "util_functions.hpp"

namespace gfx {
    std::string exportAsPPM(const Canvas& canvas)
    {
        std::ostringstream ppm_data;

        // Create the PPM header
        ppm_data << PPM_IDENTIFIER << '\n';
        ppm_data << canvas.width() << ' ' << canvas.height() << '\n';
        ppm_data << PPM_MAX_COLOR_VALUE << '\n';

        // Write the pixel data to the string
        unsigned int row_char_count = 0;
        for (int row = 0; row < canvas.height(); ++row) {
            for (int col = 0; col < canvas.width(); ++col) {

                // Scale the RGB values and convert to strings, storing in an array for iteration
                const Color pixel = canvas[col, row];
                std::array<std::string, 3> color_value_strs{
                        std::to_string(utils::clampedScale(pixel.r(), 0, PPM_MAX_COLOR_VALUE)),
                        std::to_string(utils::clampedScale(pixel.g(), 0, PPM_MAX_COLOR_VALUE)),
                        std::to_string(utils::clampedScale(pixel.b(), 0, PPM_MAX_COLOR_VALUE)) };

                // Output each scaled value to the string
                for (const std::string str: color_value_strs) {
                    // Wrap the line if the length of the data + a space will exceed PPM_MAX_LINE_LEN
                    size_t str_len = str.length();
                    if (row_char_count + str_len + 1 > PPM_MAX_LINE_LEN) {
                        ppm_data << '\n';
                        row_char_count = 0;
                    }
                        // Otherwise put a space (unless data is first value in row)
                    else if (row_char_count > 0) {
                        ppm_data << ' ';
                        ++row_char_count;
                    }

                    // Output the color data to the string
                    ppm_data << str;
                    row_char_count += str_len;
                }
            }

            // Start a new row once all the pixel data for this canvas row is output
            ppm_data << '\n';
            row_char_count = 0;
        }

        return ppm_data.str();
    }
}