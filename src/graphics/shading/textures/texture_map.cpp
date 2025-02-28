#include "texture_map.hpp"

#include <cmath>

namespace gfx {
    Vector3 ProjectionMap(const Vector4& object_point)
    {
        return create2DPoint(object_point.x(), object_point.y());
    }

    Vector3 PlanarMap(const Vector4& object_point)
    {
        return create2DPoint(std::fmod(object_point.x(), 1), std::fmod(object_point.z(), 1));
    }
}