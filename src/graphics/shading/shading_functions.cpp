#include "shading_functions.hpp"

#include <cmath>
#include <list>
#include <unordered_map>

#include "util_functions.hpp"

namespace gfx {
    Color calculateSurfaceColor(const Surface& object,
                                const PointLight& light,
                                const Vector4& point_position,
                                const Vector4& surface_normal,
                                const Vector4& view_vector,
                                const bool is_shadowed)
    {
        // The base surface color from direct light
        const Color object_color{ object.getObjectColorAt(point_position) };
        const Color effective_color{ object_color * light.intensity };

        // The direction vector to the light source
        const Vector4 light_vector{ normalize(light.position - point_position) };

        // Simulate the ambient color as a percentage of the base surface color
        const Material& material{ object.getMaterial() };
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

    std::pair<double, double> getRefractiveIndices(const Intersection& hit,
                                                   const std::vector<Intersection>& possible_overlaps)
    {
        // The order in which objects are added must be maintained, but we use a map to facilitate quick removal
        // of objects from the list at arbitrary positions without having to repeatedly search the list
        std::list<const Surface*> containing_objects_list{ };
        std::unordered_map<const Surface*, std::list<const Surface*>::iterator> object_list_iterator_map{ };

        // Assume the exited medium is air
        double n1 = 1.0;

        // Check each intersection in the possible overlaps group to find the exited & entered objects
        for (const auto& intersection : possible_overlaps) {
            // The exited medium is an overlapping object
            if (intersection == hit && !containing_objects_list.empty()) {
                n1 = containing_objects_list.back()->getMaterial().getRefractiveIndex();
            }

            const Surface* object_ptr{ &intersection.getObject() };
            if (object_list_iterator_map.contains(object_ptr)) {
                // The ray has exited this object, remove it from the list
                auto list_iter{ object_list_iterator_map[object_ptr] };
                containing_objects_list.erase(list_iter);
                object_list_iterator_map.erase(object_ptr);
            } else {
                // The ray is entering this object, append it to the end of the list
                containing_objects_list.push_back(object_ptr);
                object_list_iterator_map[object_ptr] = std::prev(containing_objects_list.end());
            }

            if (intersection == hit && !containing_objects_list.empty()) {
                // The entered medium is an overlapping object
                const double n2{ containing_objects_list.back()->getMaterial().getRefractiveIndex() };

                // Terminate loop early since the correct entered object has been found
                return std::pair<double, double>{ n1, n2 };
            }
        }

        // All intersections have been checked, the entered medium is air
        return std::pair<double, double>{ n1, 1.0 };
    }

    double calculateReflectance(const Vector4& view_vector, const Vector4& normal_vector, double n1, double n2)
    {
        // When assume initially that n₂ > n₁ and thus initially use the cosine
        // of the incident angle in Schlick's approximation
        double cos_schlick{ dotProduct(view_vector, normal_vector) };

        if (utils::isGreater(n1, n2)) {
            // Use Snell's Law to determine if θᵣ has a real solution
            const double n_ratio{ n1 / n2 };
            const double sin2_t{ std::pow(n_ratio, 2) * (1 - std::pow(cos_schlick, 2)) };
            if (utils::isGreater(sin2_t, 1.0)) {
                // Total internal reflection occurs
                return 1;
            }

            // Since n₁ > n₂, we will use the transmitted angle in Schlick's approximation
            const double cos_t{ std::sqrt(1 - sin2_t) };
            cos_schlick = cos_t;
        }

        // Compute Schlick's approximation with R₀ representing the reflectance at normal incidence (θ = 0)
        const double r_0{ std::pow((n1 - n2) / (n1 + n2), 2) };
        return r_0 + (1 - r_0) * std::pow(1 - cos_schlick, 5);
    }
}