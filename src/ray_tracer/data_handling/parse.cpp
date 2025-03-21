#include "parse.hpp"

#include <string_view>
#include <unordered_map>

#include "transform.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "cube.hpp"
#include "cylinder.hpp"
#include "cone.hpp"

#include "gradient_texture_3d.hpp"
#include "stripe_pattern_3d.hpp"
#include "ring_pattern_3d.hpp"
#include "checkered_pattern_3d.hpp"

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
        const gfx::Matrix4 view_transform_matrix{
            gfx::createViewTransformMatrix(
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
            transform_matrix = buildChained3DTransformMatrix(object_data["transform"]);
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
            transform_matrix = buildChained3DTransformMatrix(composite_surface_data["transform"]);

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
        gfx::Material material{ parseMaterialPropertyData(material_data) };

        // Set the pattern or object color
        if (material_data.contains("texture"))
            material.setTexture(parseTextureData(material_data["texture"]));
        else if (material_data.contains("color"))
            material.setTexture(gfx::ColorTexture{ parseColorData(material_data["color"]) });

        return material;
    }

    // Material Properties Parser
    gfx::MaterialProperties parseMaterialPropertyData(const json& material_data)
    {
        gfx::MaterialProperties properties{ };
        if (material_data.contains("ambient"))
            properties.ambient = material_data["ambient"].get<double>();
        if (material_data.contains("diffuse"))
            properties.diffuse = material_data["diffuse"].get<double>();
        if (material_data.contains("specular"))
            properties.specular = material_data["specular"].get<double>();
        if (material_data.contains("shininess"))
            properties.shininess = material_data["shininess"].get<double>();
        if (material_data.contains("reflectivity"))
            properties.reflectivity = material_data["reflectivity"].get<double>();
        if (material_data.contains("transparency"))
            properties.transparency = material_data["transparency"].get<double>();
        if (material_data.contains("refractive_index"))
            properties.refractive_index = material_data["refractive_index"].get<double>();

        return properties;
    }

    // Color Data Parser
    gfx::Color parseColorData(const json& color_data)
    {
        return gfx::Color{ color_data[0], color_data[1], color_data[2] };
    }

    // Texture Data Parser
    std::shared_ptr<gfx::Texture> parseTextureData(const json& texture_data)
    {
        // Define string-to-case mapping for possible textures
        enum class Cases{ Gradient, Stripe, Ring, Checkered };
        static const std::unordered_map<std::string_view, Cases> stringToCaseMap{
                { "gradient",  Cases::Gradient },
                { "stripe",    Cases::Stripe },
                { "ring",      Cases::Ring },
                { "checkered", Cases::Checkered }
        };

        // Convert the string to a Case for use in the switch statement
        std::string_view texture_type_str{ texture_data["type"].get<std::string_view>() };
        auto it{ stringToCaseMap.find(texture_type_str) };
        if (it == stringToCaseMap.end()) {
            throw std::invalid_argument("Invalid texture type, check spelling in scene data input file");
        }
        Cases texture_type{ it->second };

        // Build the transform matrix
        gfx::Matrix4 transform_matrix{ buildChained3DTransformMatrix(texture_data["transform"]) };

        // Create and return the texture
        const auto [ texture_a_ptr, texture_b_ptr ] { createPatternTextures(texture_data) };
        switch (texture_type) {
            case Cases::Gradient:
                return std::make_shared<gfx::GradientTexture3D>(
                        gfx::GradientTexture3D{
                                transform_matrix,
                                parseColorData(texture_data["color_a"]),
                                parseColorData(texture_data["color_b"])
                        });
            case Cases::Stripe:
                return std::make_shared<gfx::StripePattern3D>(
                        gfx::StripePattern3D{
                                transform_matrix,
                                *texture_a_ptr,
                                *texture_b_ptr
                        });
            case Cases::Ring:
                return std::make_shared<gfx::RingPattern3D>(
                        gfx::RingPattern3D{
                                transform_matrix,
                                *texture_a_ptr,
                                *texture_b_ptr
                        });
            case Cases::Checkered:
                return std::make_shared<gfx::CheckeredPattern3D>(
                        gfx::CheckeredPattern3D{
                                transform_matrix,
                                *texture_a_ptr,
                                *texture_b_ptr
                        });
        }
    }

    // Nested Pattern Texture Creator
    std::pair<std::shared_ptr<gfx::Texture>, std::shared_ptr<gfx::Texture>>
    createPatternTextures(const json& pattern_data)
    {
        std::shared_ptr<gfx::Texture> texture_a_ptr, texture_b_ptr;
        if (pattern_data.contains("color_a"))
            texture_a_ptr = gfx::ColorTexture{ parseColorData(pattern_data["color_a"]) }.clone();
        else if (pattern_data.contains("texture_a"))
            texture_a_ptr = parseTextureData(pattern_data["texture_a"]);
        else
            throw std::invalid_argument("Pattern must contain a definition of another pattern (as pattern_a) or a color (as color_a)");


        if (pattern_data.contains("color_b"))
            texture_b_ptr = gfx::ColorTexture{ parseColorData(pattern_data["color_b"]) }.clone();
        else if (pattern_data.contains("texture_b"))
            texture_b_ptr = parseTextureData(pattern_data["texture_b"]);
        else
            throw std::invalid_argument("Pattern must contain a definition of another pattern (as pattern_b) or a color (as color_b)");

        return { texture_a_ptr, texture_b_ptr };
    }

    // Chained 3D Transformation Matrix Builder
    gfx::Matrix4 buildChained3DTransformMatrix(const json& transform_data_list)
    {
        gfx::Matrix4 transform_matrix{ };
        for (const auto& transform_data: transform_data_list) {
            transform_matrix *= parse3DTransformMatrixData(transform_data);
        }
        return transform_matrix;
    }

    // Chained 2D Transformation Matrix Builder
    gfx::Matrix3 buildChained2DTransformMatrix(const json& transform_data_list)
    {
        gfx::Matrix3 transform_matrix{ };
        for (const auto& transform_data: transform_data_list) {
            transform_matrix *= parse2DTransformMatrixData(transform_data);
        }
        return transform_matrix;
    }

    // 3D Transform Matrix Parser
    gfx::Matrix4 parse3DTransformMatrixData(const json& transform_data)
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
                    throw std::invalid_argument("3D Translation matrix value arrays must only have 3 values");
                }
            case Cases::Scaling:
                if (transform_vals.size() == 1) {
                    return gfx::createScalingMatrix(transform_vals[0]);
                } else if (transform_vals.size() == 3) {
                    return gfx::createScalingMatrix(transform_vals[0], transform_vals[1], transform_vals[2]);
                } else {
                    throw std::invalid_argument("3D Scaling matrix value arrays must only have 1 or 3 values");
                }
            case Cases::XRotation:
                if (transform_vals.size() == 1) {
                    return gfx::createXRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("3D X-axis rotation matrix value arrays must only have 1 value");
                }
            case Cases::YRotation:
                if (transform_vals.size() == 1) {
                    return gfx::createYRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("3D Y-axis rotation matrix value arrays must only have 1 value");
                }
            case Cases::ZRotation:
                if (transform_vals.size() == 1) {
                    return gfx::createZRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("3D Z-axis rotation matrix value arrays must only have 1 value");
                }
            case Cases::Skew:
                if (transform_vals.size() == 6) {
                    return gfx::createSkewMatrix(transform_vals[0], transform_vals[1], transform_vals[2],
                                                 transform_vals[3], transform_vals[4], transform_vals[5]);
                } else {
                    throw std::invalid_argument("3D Skew matrix value arrays must only have 6 values");
                }
        }
    }

    // 2D Transform Matrix Parser
    gfx::Matrix3 parse2DTransformMatrixData(const json& transform_data)
    {
        // Define string-to-case mapping for possible transform matrices
        enum class Cases{ Translation, Scaling, Rotation, XReflection, YReflection, XSkew, YSkew };
        static const std::unordered_map<std::string_view, Cases> stringToCaseMap{
                { "translate",  Cases::Translation },
                { "scale",      Cases::Scaling },
                { "rotate",     Cases::Rotation },
                { "reflect_x",  Cases::XReflection },
                { "reflect_y",  Cases::YReflection },
                { "skew_x",     Cases::XSkew },
                { "skew_y",     Cases::YSkew }
        };

        // Convert the string to a Case for use in the switch statement
        std::string_view transform_type_str{ transform_data["type"].get<std::string_view>() };
        auto it{ stringToCaseMap.find(transform_type_str) };
        if (it == stringToCaseMap.end()) {
            throw std::invalid_argument("Invalid transform matrix type, check spelling in scene data input file");
        }
        Cases matrix_type{ it->second };

        // Return the appropriate matrix based on the matrix type
        std::vector<double> transform_vals{ };
        if (transform_data.contains("values"))
            transform_vals.append_range(transform_data["values"].get<std::vector<double>>());
        switch (matrix_type) {
            case Cases::Translation:
                if (transform_vals.size() == 2) {
                    return gfx::create2DTranslationMatrix(transform_vals[0], transform_vals[1]);
                } else {
                    throw std::invalid_argument("2D Translation matrix value arrays must only have 2 values");
                }
            case Cases::Scaling:
                if (transform_vals.size() == 1) {
                    return gfx::create2DScalingMatrix(transform_vals[0]);
                } else if (transform_vals.size() == 2) {
                    return gfx::create2DScalingMatrix(transform_vals[0], transform_vals[1]);
                } else {
                    throw std::invalid_argument("2D Scaling matrix value arrays must only have 1 or 2 values");
                }
            case Cases::Rotation:
                if (transform_vals.size() == 1) {
                    return gfx::create2DRotationMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("2D Rotation matrix value arrays must only have 1 value");
                }
            case Cases::XReflection:
                return gfx::create2DHorizontalReflectionMatrix();
            case Cases::YReflection:
                return gfx::create2DVerticalReflectionMatrix();
            case Cases::XSkew:
                if (transform_vals.size() == 1) {
                    return gfx::create2DHorizontalSkewMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("2D Horizontal skew matrix value arrays must only have 1 value");
                }
            case Cases::YSkew:
                if (transform_vals.size() == 1) {
                    return gfx::create2DVerticalSkewMatrix(transform_vals[0]);
                } else {
                    throw std::invalid_argument("2D Vertical skew matrix value arrays must only have 1 value");
                }
        }
    }
}