#pragma once

#include "nlohmann/json.hpp"

#include "matrix4.hpp"

using json = nlohmann::json;

namespace data {

    // Returns the appropriate transformation matrix based on the JSON description of the desired matrix
    [[nodiscard]] gfx::Matrix4 parseTransformMatrixData(const json& transform_data);
}