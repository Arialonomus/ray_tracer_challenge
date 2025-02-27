#pragma once

#include <memory>

#include "nlohmann/json.hpp"

#include "world.hpp"
#include "camera.hpp"
#include "surface.hpp"
#include "pattern.hpp"
#include "color.hpp"
#include "matrix4.hpp"

#include "composite_surface.hpp"

using json = nlohmann::json;

struct Scene{
    gfx::World world;
    rt::Camera camera;
};

namespace data {
    /* JSON Scene Data Functions */

    // Reads a JSON file containing scene data and returns a Scene struct
    // containing the world and camera defined by the scene data
    [[nodiscard]] Scene parseSceneData(const json& scene_data);

    // Returns a pointer to a newly created shape described by the passed-in JSON data
    [[nodiscard]] std::shared_ptr<gfx::Object> parseObjectData(const json& object_data);

    // Returns a pointer to a newly created composite surface described by the passed-in JSON data
    [[nodiscard]] std::shared_ptr<gfx::CompositeSurface> parseCompositeSurfaceData(const json& composite_surface_data);

    // Returns a newly constructed material based on the passed in material data
    [[nodiscard]] gfx::Material parseMaterialData(const json& material_data);

    // Returns a pointer to a newly created pattern described by the passed-in JSON data
    [[nodiscard]] std::unique_ptr<gfx::Pattern> parsePatternData(const json& pattern_data);

    // Returns a color object described by the passed in JSON data
    [[nodiscard]] gfx::Color parseColorData(const json& color_data);

    // Builds a transform matrix from the array of transform matrices described by the passed-in JSON data
    [[nodiscard]] gfx::Matrix4 buildChainedTransformMatrix(const json& transform_data_list);

    // Returns the appropriate 3D transformation matrix based on the JSON description of the desired matrix
    [[nodiscard]] gfx::Matrix4 parse3DTransformMatrixData(const json& transform_data);

    // Returns the appropriate 2D transformation matrix based on the JSON description of the desired matrix
    [[nodiscard]] gfx::Matrix3 parse2DTransformMatrixData(const json& transform_data);
}