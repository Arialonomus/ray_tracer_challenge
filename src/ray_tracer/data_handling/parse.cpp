#include "parse.hpp"

#include <string_view>
#include <unordered_map>

#include "transform.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "cube.hpp"
#include "cylinder.hpp"
#include "cone.hpp"

#include "stripe_pattern.hpp"
#include "gradient_pattern.hpp"
#include "ring_pattern.hpp"
#include "checkered_pattern.hpp"

namespace data {
    // Scene Data Parser
    Scene parseSceneData(const json& scene_data)
    {
        // Get the light source data
        const json& light_source_data{ scene_data["world"]["light_source"] };
        const std::vector<double> intensity_vals{
                light_source_data["intensity"].get<std::vector<double>>() };
        const std::vector<double> position_vals{
                light_source_data["position"].get<std::vector<double>>() };
        const gfx::PointLight light_source{
                gfx::Color{ intensity_vals[0], intensity_vals[1], intensity_vals[2] },
                gfx::createPoint(position_vals[0], position_vals[1], position_vals[2]) };

        // Create the world with the light source
        gfx::World world{ light_source };

        // Add all the objects to the scene
        const json& object_data_list{ scene_data["world"]["objects"] };
        for (const auto& object_data: object_data_list) {
            world.addObject(parseObjectData(object_data));
        }

        // Get the camera data
        const json& camera_data{ scene_data["camera"] };
        const std::vector<double> input_base_vals{ camera_data["transform"]["input_base"].get<std::vector<double>>() };
        const std::vector<double> output_base_vals{
                camera_data["transform"]["output_base"].get<std::vector<double>>() };
        const std::vector<double> up_vector_vals{ camera_data["transform"]["up_vector"].get<std::vector<double>>() };

        // Build the view transform matrix
        const gfx::Matrix4 view_transform_matrix{ gfx::createViewTransformMatrix(
                gfx::createPoint(input_base_vals[0], input_base_vals[1], input_base_vals[2]),
                gfx::createPoint(output_base_vals[0], output_base_vals[1], output_base_vals[2]),
                gfx::createVector(up_vector_vals[0], up_vector_vals[1], up_vector_vals[2])
        )
        };

        // Create the camera
        const rt::Camera camera{
                camera_data["viewport_width"],
                camera_data["viewport_height"],
                camera_data["field_of_view"],
                view_transform_matrix
        };

        return Scene{ world, camera };
    }

    // Renderable Object Parser
    std::shared_ptr<gfx::Object> parseObjectData(const json& object_data)
    {
        // Build composite surface, if applicable
        std::string_view shape_type_str{ object_data["shape"].get<std::string_view>() };
        if (shape_type_str == "composite_surface") {
            return parseCompositeSurfaceData(object_data);
        }

        // Define string-to-case mapping for possible shape primitives
        enum class Cases { Plane, Sphere, Cube, Cylinder, Cone };
        static const std::unordered_map<std::string_view, Cases> stringToCaseMap{
                { "plane",              Cases::Plane },
                { "sphere",             Cases::Sphere },
                { "cube",               Cases::Cube },
                { "cylinder",           Cases::Cylinder },
                { "cone",               Cases::Cone }
        };

        // Convert the string to a Case for use in the switch statement
        auto it{ stringToCaseMap.find(shape_type_str) };
        if (it == stringToCaseMap.end()) {
            throw std::invalid_argument("Invalid shape type, check spelling in scene data input file");
        }
        Cases shape_type{ it->second };

        // Build the transform matrix
        gfx::Matrix4 transform_matrix{ gfx::createIdentityMatrix() };
        if (object_data.contains("transform")) {
            transform_matrix = buildChainedTransformMatrix(object_data["transform"]);
        }

        // Extract the material data
        gfx::Material material{ };
        if (object_data.contains("material")) {
            material = parseMaterialData(object_data["material"]);
        }

        // Store values for unbounded shapes, if present
        const double y_min{ object_data.contains("y_min") ?
            object_data["y_min"].get<double>() : -std::numeric_limits<double>::infinity()
        };
        const double y_max{ object_data.contains("y_max") ?
            object_data["y_max"].get<double>() : std::numeric_limits<double>::infinity()
        };
        const bool is_closed{ object_data.contains("is_closed") && object_data["is_closed"].get<bool>() };

        // Create and return the object
        switch (shape_type) {
            case Cases::Plane:
                return std::make_shared<gfx::Plane>(gfx::Plane{ transform_matrix, material });
            case Cases::Sphere:
                return std::make_shared<gfx::Sphere>(gfx::Sphere{ transform_matrix, material });
            case Cases::Cube:
                return std::make_shared<gfx::Cube>(gfx::Cube{ transform_matrix, material });
            case Cases::Cylinder:
                return std::make_shared<gfx::Cylinder>(gfx::Cylinder{transform_matrix, material,
                                                                     y_min, y_max, is_closed });
            case Cases::Cone:
                return std::make_shared<gfx::Cone>(gfx::Cone{transform_matrix, material,
                                                             y_min, y_max, is_closed });
        }
    }

    // Composite Surface Builder
    std::shared_ptr<gfx::CompositeSurface> parseCompositeSurfaceData(const json& composite_surface_data)
    {
        // Build the transform matrix, if present
        gfx::Matrix4 transform_matrix{ gfx::createIdentityMatrix() };
        if (composite_surface_data.contains("transform"))
            transform_matrix = buildChainedTransformMatrix(composite_surface_data["transform"]);

        // Construct the composite surface
        std::shared_ptr<gfx::CompositeSurface> composite_surface_ptr{ std::make_shared<gfx::CompositeSurface>(transform_matrix) };

        // Extract the material data, if present
        if(composite_surface_data.contains("material"))
            composite_surface_ptr->addMaterial(parseMaterialData(composite_surface_data["material"]));

        // Add the child objects to the composite surface
        const json& child_data_list{ composite_surface_data["children"] };
        for (const auto& child_data: child_data_list) {
            composite_surface_ptr->addChild(parseObjectData(child_data));
        }
        return composite_surface_ptr;
    }

    // Material Data Parser
    gfx::Material parseMaterialData(const json& material_data)
    {
        // Parse the material attribute data
        gfx::Material material{
            material_data.contains("ambient") ? material_data["ambient"].get<double>() : 0.1,
            material_data.contains("diffuse") ? material_data["diffuse"].get<double>() : 0.9,
            material_data.contains("specular") ? material_data["specular"].get<double>() : 0.9,
            material_data.contains("shininess") ? material_data["shininess"].get<double>() : 200,
            material_data.contains("reflectivity") ? material_data["reflectivity"].get<double>() : 0,
            material_data.contains("transparency") ? material_data["transparency"].get<double>() : 0,
            material_data.contains("refractive_index") ? material_data["refractive_index"].get<double>() : 1
        };

        // Set the pattern or object color
        if (material_data.contains("pattern"))
            material.setPattern(parsePatternData(material_data["pattern"]));
        else
            material.setColor(parseColorData(material_data["color"]));

        return material;
    }

    // Pattern Data Parser
    std::unique_ptr<gfx::Pattern> parsePatternData(const json& pattern_data)
    {
        // Define string-to-case mapping for possible patterns
        enum class Cases{ Stripe, Gradient, Ring, Checkered };
        static const std::unordered_map<std::string_view, Cases> stringToCaseMap{
                { "stripe",    Cases::Stripe },
                { "gradient",  Cases::Gradient },
                { "ring",      Cases::Ring },
                { "checkered", Cases::Checkered }
        };

        // Convert the string to a Case for use in the switch statement
        std::string_view pattern_type_str{ pattern_data["type"].get<std::string_view>() };
        auto it{ stringToCaseMap.find(pattern_type_str) };
        if (it == stringToCaseMap.end()) {
            throw std::invalid_argument("Invalid pattern type, check spelling in scene data input file");
        }
        Cases pattern_type{ it->second };

        // Build the transform matrix
        gfx::Matrix4 transform_matrix{ buildChainedTransformMatrix(pattern_data["transform"]) };

        // Create and return the pattern
        switch (pattern_type) {
            case Cases::Stripe:
                return std::make_unique<gfx::StripePattern>(
                        gfx::StripePattern{
                                transform_matrix,
                                parseColorData(pattern_data["color_a"]),
                                parseColorData(pattern_data["color_b"])
                        });
            case Cases::Gradient:
                return std::make_unique<gfx::GradientPattern>(
                        gfx::GradientPattern{
                                transform_matrix,
                                parseColorData(pattern_data["color_a"]),
                                parseColorData(pattern_data["color_b"])
                        });
            case Cases::Ring:
                return std::make_unique<gfx::RingPattern>(
                        gfx::RingPattern{
                                transform_matrix,
                                parseColorData(pattern_data["color_a"]),
                                parseColorData(pattern_data["color_b"])
                        });
            case Cases::Checkered:
                return std::make_unique<gfx::CheckeredPattern>(
                        gfx::CheckeredPattern{
                                transform_matrix,
                                parseColorData(pattern_data["color_a"]),
                                parseColorData(pattern_data["color_b"])
                        });
        }
    }

    // Color Data Parser
    gfx::Color parseColorData(const json& color_data)
    {
        return gfx::Color{ color_data[0], color_data[1], color_data[2] };
    }

    // Chained Transformation Matrix Builder
    gfx::Matrix4 buildChainedTransformMatrix(const json& transform_data_list)
    {
        gfx::Matrix4 transform_matrix{ gfx::createIdentityMatrix() };
        for (const auto& transform_data: transform_data_list) {
            transform_matrix *= parseTransformMatrixData(transform_data);
        }
        return transform_matrix;
    }

    // Transform Matrix Parser
    gfx::Matrix4 parseTransformMatrixData(const json& transform_data)
    {
        // Define string-to-case mapping for possible transform matrices
        enum class Cases{ Translation, Scaling, XRotation, YRotation, ZRotation, Skew };
        static const std::unordered_map<std::string_view, Cases> stringToCaseMap{
                { "translate", Cases::Translation },
                { "scale",     Cases::Scaling },
                { "rotate_x",  Cases::XRotation },
                { "rotate_y",  Cases::YRotation },
                { "rotate_z",  Cases::ZRotation },
                { "skew",      Cases::Skew }
        };

        // Convert the string to a Case for use in the switch statement
        std::string_view transform_type_str{ transform_data["type"].get<std::string_view>() };
        auto it{ stringToCaseMap.find(transform_type_str) };
        if (it == stringToCaseMap.end()) {
            throw std::invalid_argument("Invalid transform matrix type, check spelling in scene data input file");
        }
        Cases matrix_type{ it->second };

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
        }
    }
}