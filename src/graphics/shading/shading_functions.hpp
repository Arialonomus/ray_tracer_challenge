#pragma once

#include "color.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "vector4.hpp"
#include "intersection.hpp"

namespace gfx {
    // Returns the surface color of an object at a surface point, calculated using the Phong Shading Model
    [[nodiscard]] Color calculateSurfaceColor(const Shape& object,
                                              const PointLight& light,
                                              const Vector4& point_position,
                                              const Vector4& surface_normal,
                                              const Vector4& view_vector,
                                              bool is_shadowed = false);


    // Returns a pair containing the refractive indices for a ray-object intersection within
    // a group of intersections of potentially overlapping objects
    [[nodiscard]] std::pair<double, double> getRefractiveIndices(const Intersection& intersection,
                                                                 const std::vector<Intersection>& possible_overlaps);

    // Calculates the reflectance of a surface using the Schlick approximation to Fresnel's equations
    [[nodiscard]] double calculateReflectance(const Vector4& view_vector,
                                              const Vector4& normal_vector,
                                              double n1, double n2);
}