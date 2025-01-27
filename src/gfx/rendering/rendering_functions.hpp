#pragma once

#include "color.hpp"
#include "material.hpp"
#include "light.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Shading Calculations */

    // Returns the surface color of an object at a surface point, calculated using the Phong Shading Model
    [[nodiscard]] Color calculateSurfaceColor(const Material& material,
                                              const PointLight& light,
                                              const Vector4& point_position,
                                              const Vector4& surface_normal,
                                              const Vector4& view_vector);
}