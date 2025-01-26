#include "shading_functions.hpp"

#include <cmath>

namespace gfx {
    Color calculateSurfaceColor(const Material& material,
                                      const PointLight& light,
                                      const Vector4& point_position,
                                      const Vector4& surface_normal,
                                      const Vector4& view_vector)
    {
        // Calculate the base color as affected cast by the light's color/intensity
        const Color effective_color{ material.color * light.intensity };

        // Calculate the direction to the light source
        const Vector4 light_vector{ light.position - point_position };

        // Calculate the ambient component
        const Color ambient{ effective_color * material.ambient };

        // Check if the light is on the same side of the surface as the viewpoint
        Color diffuse{ 0, 0, 0 };
        Color specular{ 0, 0, 0 };
        const float light_normal_cosine{ dotProduct(light_vector, surface_normal) };
        if (light_normal_cosine >= 0)
        {
            // Compute the diffuse component
            diffuse = effective_color * material.diffuse * light_normal_cosine;

            // Check if the light reflects toward the viewpoint
            const Vector4 reflection_vector{ -light_vector.reflect(surface_normal) };
            const float light_view_cosine{ dotProduct(reflection_vector, view_vector) };
            if (light_view_cosine >= 0) {
                // Calculate the specular component
                const float specular_exponent{ std::powf(light_view_cosine, material.shininess) };
                specular = light.intensity * material.specular * specular_exponent;
            }
        }

        // Sum the three components of the model and return
        return ambient + diffuse + specular;
    }
}