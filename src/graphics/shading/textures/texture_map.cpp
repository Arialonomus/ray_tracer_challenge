#include "texture_map.hpp"

namespace gfx {
    Vector3 ProjectionMap(const Vector4& object_point)
    {
        return create2DPoint(object_point.x(), object_point.z());
    }
}