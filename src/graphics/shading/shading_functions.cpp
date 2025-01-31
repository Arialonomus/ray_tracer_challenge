#include "shading_functions.hpp"

#include <cmath>

#include "util_functions.hpp"

namespace gfx {
    Color calculateSurfaceColor(const Material& material,
                                const PointLight& light,
                                const Vector4& point_position,
                                const Vector4& surface_normal,
                                const Vector4& view_vector,
                                const bool is_shadowed)
    {
        // The base surface color from direct light
        const Color object_color{ material.hasPattern() ?
                                  material.getPattern().samplePatternAt(point_position)
            : material.getColor() };
        const Color effective_color{ object_color * light.intensity };

        // The direction vector to the light source
        const Vector4 light_vector{ normalize(light.position - point_position) };

        // Simulate the ambient color as a percentage of the base surface color
        const Color ambient{ effective_color * material.getAmbient() };

        // Check if the light is on the same side of the surface as the viewpoint
        Color diffuse{ 0, 0, 0 };
        Color specular{ 0, 0, 0 };
        const double light_normal_cosine{ dotProduct(light_vector, surface_normal) };
        if (utils::isGreaterOrEqual(light_normal_cosine, 0.0) && !is_shadowed)
        {
            // Diffuse term is calculated as a ratio in relation to the angle of the incoming light
            diffuse = effective_color * material.getDiffuse() * light_normal_cosine;

            // Check if the light reflects toward the viewpoint
            const Vector4 reflection_vector{ -light_vector.reflect(surface_normal) };
            const double light_view_cosine{ dotProduct(reflection_vector, view_vector) };
            if (utils::isGreater(light_view_cosine, 0.0)) {
                // Specular reflection is dependent on the specular exponent which is a factor of the shininess value
                const double specular_exponent{ std::pow(light_view_cosine, material.getShininess()) };
                specular = light.intensity * material.getSpecular() * specular_exponent;
            }
        }

        // Sum the three components of the model and return
        return ambient + diffuse + specular;
    }
}