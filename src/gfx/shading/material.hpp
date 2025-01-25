#pragma once

#include "color.hpp"

namespace gfx {
    struct Material {
        Color color{ 1, 1, 1 };
        float ambient{ 0.1 };
        float diffuse{ 0.9 };
        float specular{ 0.9 };
        float shininess{ 200 };
    };
}
