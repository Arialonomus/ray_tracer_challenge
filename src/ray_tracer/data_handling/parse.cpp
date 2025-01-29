#include "parse.hpp"

#include <string_view>
#include <unordered_map>

#include "transform.hpp"

namespace data{
    Scene parseSceneData(const json& scene_data)
    {
        // Get the light source data
        const json& light_source_data{ scene_data["world"]["light_source"] };
        const std::vector<double> intensity_vals{
            light_source_data["intensity"].get<std::vector<double>>() };
        const std::vector<double> position_vals{
            light_source_data["position"].get<std::vector<double>>() };
        const gfx::PointLight light_source {
            gfx::Color{ intensity_vals[0], intensity_vals[1], intensity_vals[2] },
            gfx::createPoint(position_vals[0], position_vals[1], position_vals[2]) };

        // Create the world with the light source
        gfx::World world{ light_source };

        // Get the object data
        const json& object_data_list{ scene_data["world"]["objects"] };
        for (const auto& object_data : object_data_list) {
            // Build the transform matrix
            gfx::Matrix4 transform_matrix{ buildChainedTransformMatrix(object_data["transform"]) };

            // Extract the material data
            const json& material_data{ object_data["material"] };
            const std::vector<double> color_vals{
                material_data["color"].get<std::vector<double>>() };
            const gfx::Material material{
                gfx::Color{ color_vals[0], color_vals[1], color_vals[2] },
                material_data["ambient"],
                material_data["diffuse"],
                material_data["specular"],
                material_data["shininess"]
            };

            // Create the object and add to the object list
            const gfx::Sphere object{ transform_matrix, material };
            world.addObject(object);
        }

        // Get the camera data
        const json& camera_data{ scene_data["camera"] };
        const std::vector<double> input_base_vals{ camera_data["transform"]["input_base"].get<std::vector<double>>() };
        const std::vector<double> output_base_vals{ camera_data["transform"]["output_base"].get<std::vector<double>>() };
        const std::vector<double> up_vector_vals{ camera_data["transform"]["up_vector"].get<std::vector<double>>() };

        // Build the view transform matrix
        const gfx::Matrix4 view_transform_matrix{ gfx::createViewTransformMatrix(
                gfx::createPoint(input_base_vals[0], input_base_vals[1], input_base_vals[2]),
                gfx::createPoint(output_base_vals[0], output_base_vals[1], output_base_vals[2]),
                gfx::createVector(up_vector_vals[0], up_vector_vals[1], up_vector_vals[2])
                )
        };
        const rt::Camera camera{
            camera_data["viewport_width"],
            camera_data["viewport_height"],
            camera_data["field_of_view"],
            view_transform_matrix
        };

        return Scene{ world, camera };
    }

    gfx::Matrix4 buildChainedTransformMatrix(const json& transform_data_list)
    {
        gfx::Matrix4 transform_matrix{ gfx::createIdentityMatrix() };
        for (const auto& transform_data : transform_data_list) {
            transform_matrix *= parseTransformMatrixData(transform_data);
        }

        return transform_matrix;
    }

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
        const std::vector<double> transform_vals{ transform_data["values"].get<std::vector<double>>() };
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