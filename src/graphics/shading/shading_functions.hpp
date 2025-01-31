#pragma once

#include "color.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "vector4.hpp"

namespace gfx {
    // Returns the surface color of an object at a surface point, calculated using the Phong Shading Model
    [[nodiscard]] Color calculateSurfaceColor(const Shape& object,
                                              const PointLight& light,
                                              const Vector4& point_position,
                                              const Vector4& surface_normal,
                                              const Vector4& view_vector,
                                              bool is_shadowed = false);
}