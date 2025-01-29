#pragma once

#include "nlohmann/json.hpp"

#include "matrix4.hpp"

using json = nlohmann::json;

namespace data {
    // Builds a transform matrix from the array of transform matrices described by the passed-in JSON data
    [[nodiscard]] gfx::Matrix4 buildChainedTransformMatrix(const json& transform_data_list);

    // Returns the appropriate transformation matrix based on the JSON description of the desired matrix
    [[nodiscard]] gfx::Matrix4 parseTransformMatrixData(const json& transform_data);
}