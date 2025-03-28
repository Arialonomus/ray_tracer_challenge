#include "world.hpp"

#include <algorithm>

#include "surface.hpp"
#include "util_functions.hpp"
#include "shading_functions.hpp"

namespace gfx {
    // Point Light Constructor
    World::World(const PointLight& light_source)
            : m_light_source{ light_source }
    {}

    // Object Inserter (from object ref)
    void World::addObject(const Object& object)
    {
        m_objects.push_back(object.clone());
    }

    // Object Inserter (from pointer)
    void World::addObject(const std::shared_ptr<Object>& object)
    {
        m_objects.push_back(object);
    }

    // World Intersection Calculator
    std::vector<Intersection> World::getAllIntersections(const Ray& ray) const
    {
        std::vector<Intersection> world_intersections{ };

        // Determine intersections for each object and aggregate into a single list
        for (const auto& object : m_objects) {
            std::vector<Intersection> object_intersections{ object->getObjectIntersections(ray) };
            world_intersections.insert(world_intersections.end(),
                                       object_intersections.begin(),
                                       object_intersections.end());
        }

        // Sort list and return
        std::sort(world_intersections.begin(), world_intersections.end());
        return world_intersections;
    }

    bool World::isShadowed(const Vector4& point) const
    {
        // Get the direction vector to the light source
        const Vector4 light_source_displacement{ m_light_source.position - point };

        // Cast a ray towards the light source to see if it intersects with any other object
        const Ray shadow_ray( point, normalize(light_source_displacement));
        const auto possible_hit{ getHit(this->getAllIntersections(shadow_ray)) };

        // If the intersection occurs closer than the distance to the vector, the point is shadowed
        if (possible_hit && utils::isLess(possible_hit.value().getT(), light_source_displacement.magnitude())) {
            return true;
        }

        return false;
    }

    Color World::calculatePixelColor(const Ray& ray, const int remaining_bounces) const
    {
        // Get the list of intersections for the ray and check for a hit
        const std::vector<Intersection> world_intersections{ this->getAllIntersections(ray) };
        auto possible_hit{ getHit(world_intersections) };

        // Hit found calculate the color at that position
        if (possible_hit) {
            // Pre-compute values to utilize in shadow, reflection, and refraction calculations
            const DetailedIntersection detailed_hit{ possible_hit.value(), ray };
            const bool is_shadowed{ this->isShadowed(detailed_hit.getOverPoint()) };
            const Color reflected_color{ this->calculateReflectedColorAt(detailed_hit, remaining_bounces) };
            const Color refracted_color{ this->calculateRefractedColorAt(detailed_hit,
                                                                         world_intersections,
                                                                         remaining_bounces) };

            // Calculate the surface color using the shading model
            Color surface_color{ calculateSurfaceColor(detailed_hit.getObject(),
                                                       m_light_source,
                                                       detailed_hit.getOverPoint(),
                                                       detailed_hit.getSurfaceNormal(),
                                                       detailed_hit.getViewVector(),
                                                       is_shadowed) };

            // Apply Fresnel Effect for reflective transparent materials,
            const Material hit_material{ detailed_hit.getObject().getMaterial() };
            if (utils::isGreater(hit_material.getProperties().reflectivity, 0.0) &&
                utils::isGreater(hit_material.getProperties().transparency, 0.0))
            {
                const auto [ n1, n2 ] { getRefractiveIndices(detailed_hit, world_intersections) };
                const double reflectance{ calculateReflectance(detailed_hit.getViewVector(),
                                                               detailed_hit.getSurfaceNormal(),
                                                               n1, n2) };
                return surface_color + (reflected_color * reflectance) + (refracted_color * (1 - reflectance));
            }

            // Otherwise return calculated color
            return surface_color + reflected_color + refracted_color;
        }
        // No hit found, return black
        else {
            return black();
        }
    }

    Color World::calculateReflectedColorAt(const DetailedIntersection& intersection, int remaining_bounces) const
    {
        // Bounce a ray to see what colors the reflective surface picks up
        const Material& object_material{ intersection.getObject().getMaterial() };
        const double object_reflectivity{ object_material.getProperties().reflectivity };
        if (utils::areNotEqual(object_reflectivity, 0.0) && remaining_bounces > 0) {
            const Ray reflection_vector{ intersection.getOverPoint(),
                                         intersection.getReflectionVector() };
            return object_reflectivity * this->calculatePixelColor(reflection_vector, remaining_bounces - 1);
        }
        // Non-reflective surface, return black
        else {
            return black();
        }
    }

    Color World::calculateRefractedColorAt(const DetailedIntersection& intersection,
                                           const std::vector<Intersection>& possible_overlaps,
                                           const int remaining_bounces) const
    {
        const Material& object_material{ intersection.getObject().getMaterial() };
        const double object_transparency{ object_material.getProperties().transparency };
        if (utils::areNotEqual(object_transparency, 0.0) && remaining_bounces > 0) {
            // Calculate the trig values for the angles of refraction using Snell's Law: θᵢ/θᵣ = n2/n1
            // Assume θᵢ is the angle of incidence and θᵣ is the angle of refraction
            const auto [ n1, n2 ] { getRefractiveIndices(intersection, possible_overlaps) };
            const Vector4 view_vector{ intersection.getViewVector() };
            const Vector4 normal_vector{ intersection.getSurfaceNormal() };

            // θᵢ is formed by the view vector and the normal, so the cos(θᵢ) is their dot product
            const double cos_i{ dotProduct(view_vector, normal_vector) };

            // Using the identity sin²θ + cos²θ = 1 gives us sin²(θᵣ) = (n1 / n2)² * (1 - cos²(θᵢ))
            const double n_ratio{ n1 / n2 };
            const double sin2_r{ std::pow(n_ratio, 2) * (1 - std::pow(cos_i, 2)) };

            // Total internal reflection occurs when no real solution exists for θᵣ, i.e. when sin²(θᵣ) exceeds 1
            if (utils::isGreater(sin2_r, 1.0)) {
                return black();
            }

            // Use the refraction formula to calculate the refraction direction and create the refraction ray
            const double cos_r{ std::sqrt(1 - sin2_r) };
            const Ray refraction_ray{ intersection.getUnderPoint(),
                                      normal_vector * (n_ratio * cos_i - cos_r) - view_vector * n_ratio };

            // Recursively calculate the refracted color
            return object_transparency * this->calculatePixelColor(refraction_ray, remaining_bounces - 1) ;
        } else {
            // Opaque object or maximum recursion, return black
            return black();
        }
    }
}