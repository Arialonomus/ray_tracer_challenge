#pragma once

#include <memory>

#include "nlohmann/json.hpp"

#include "world.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include "matrix4.hpp"

using json = nlohmann::json;

struct Scene{
    gfx::World world;
    rt::Camera camera;
};

namespace data {
    /* Scene Data Functions */

    // Reads a JSON file containing scene data and returns a Scene struct
    // containing the world and camera defined by the scene data
    [[nodiscard]] Scene parseSceneData(const json& scene_data);

    // Returns a pointer to a newly created shape described by the passed-in JSON data
    [[nodiscard]] std::shared_ptr<gfx::Shape> parseObjectData(const json& object_data);

    // Builds a transform matrix from the array of transform matrices described by the passed-in JSON data
    [[nodiscard]] gfx::Matrix4 buildChainedTransformMatrix(const json& transform_data_list);

    // Returns the appropriate transformation matrix based on the JSON description of the desired matrix
    [[nodiscard]] gfx::Matrix4 parseTransformMatrixData(const json& transform_data);
}