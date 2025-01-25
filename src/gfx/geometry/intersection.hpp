#pragma once

#include "sphere.hpp"

namespace gfx {
    struct Intersection {
        const float t;
        const Sphere& object;
    };
}
