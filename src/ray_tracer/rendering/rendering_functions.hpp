#pragma once

#include "color.hpp"
#include "material.hpp"
#include "light.hpp"
#include "vector4.hpp"
#include "canvas.hpp"
#include "world.hpp"
#include "camera.hpp"

namespace rt {
    // Returns a canvas containing the rendered image of a world from the viewpoint of the passed-in camera
    [[nodiscard]] rt::Canvas render(const gfx::World& world, const rt::Camera& camera);
}