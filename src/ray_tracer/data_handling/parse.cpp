#include "parse.hpp"

#include <string_view>
#include <unordered_map>

#include "transform.hpp"

namespace data{
    gfx::Matrix4 parseTransformMatrixData(const json& transform_data)
    {
        // Define string-to-case mapping for possible transform matrices
        enum class Cases{ Translation, Scaling, XRotation, YRotation, ZRotation, Skew, Default };
        static const std::unordered_map<std::string_view, Cases> stringToCaseMap{
                {"translate", Cases::Translation},
                {"scale", Cases::Scaling},
                {"rotate_x", Cases::XRotation},
                {"rotate_y", Cases::YRotation},
                {"rotate_z", Cases::ZRotation},
                {"skew", Cases::Skew}
        };

        // Convert the string to a Case for use in the switch statement
        std::string_view transform_type_str{ transform_data["type"].get<std::string_view>() };
        Cases matrix_type{ Cases::Default };
        auto it{ stringToCaseMap.find(transform_type_str) };
        if (it != stringToCaseMap.end()) {
            matrix_type = it->second;
        }

        // Return the appropriate matrix based on the matrix type
        const std::vector<float> transform_vals{ transform_data["values"].get<std::vector<float>>() };
        switch (matrix_type) {
            case Cases::Translation:
                if (transform_vals.size() == 3) {
                    return gfx::createTranslationMatrix(transform_vals[0], transform_vals[1], transform_vals[2]);
                } else {
                    throw std::invalid_argument("Translation matrix value arrays must only have 3 values");
                }
            case Cases::Scaling:
                if (transform_vals.size() == 1) {
                    return gfx::createScalingMatrix(transform_vals[0]);
                } else if (transform_vals.size() == 3) {
                    return gfx::createScalingMatrix(transform_vals[0], transform_vals[1], transform_vals[2]);
                } else {
                    throw std::invalid_argument("Scaling matrix value arrays must only have 1 or 3 values");
                }
            case Cases::XRotation:
                if (transform_vals.size() == 1) {
                    return gfx::createXRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("X-axis rotation matrix value arrays must only have 1 value");
                }
            case Cases::YRotation:
                if (transform_vals.size() == 1) {
                    return gfx::createYRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("Y-axis rotation matrix value arrays must only have 1 value");
                }
            case Cases::ZRotation:
                if (transform_vals.size() == 1) {
                    return gfx::createZRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("Z-axis rotation matrix value arrays must only have 1 value");
                }
            case Cases::Skew:
                if (transform_vals.size() == 6) {
                    return gfx::createSkewMatrix(transform_vals[0], transform_vals[1], transform_vals[2],
                                                 transform_vals[3], transform_vals[4], transform_vals[5]);
                } else {
                    throw std::invalid_argument("Skew matrix value arrays must only have 6 values");
                }
            default:
                throw std::invalid_argument("Invalid transform matrix type, check spelling in scene data input file");
        }
    }
}