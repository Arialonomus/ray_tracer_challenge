#pragma once

#include "color.hpp"
#include "vector4.hpp"

namespace gfx {
    struct PointLight {
        Color intensity{ 1, 1, 1 };
        Vector4 position{ 0, 0, 0, 1 };
    };
}