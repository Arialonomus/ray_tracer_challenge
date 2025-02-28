#pragma once

#include <functional>

#include "vector3.hpp"
#include "vector4.hpp"

namespace gfx {
    using TextureMap = std::function<Vector3(const Vector4&)>;

    // A direct mapping of the object x- and y-coordinates to texture space
    [[nodiscard]] Vector3 ProjectionMap(const Vector4& object_point);

    // A planar projection of the
    [[nodiscard]] Vector3 PlanarMap(const Vector4& object_point);
}
