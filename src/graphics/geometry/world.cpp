#include "world.hpp"

#include <algorithm>

#include "shape.hpp"
#include "util_functions.hpp"
#include "shading_functions.hpp"

namespace gfx {
    // Point Light Constructor
    World::World(const PointLight& light_source)
            : m_light_source{ light_source }
    {}

    // Object Inserter (from object ref)
    void World::addObject(const Shape& object)
    {
        m_objects.push_back(object.clone());
    }

    // Object Inserter (from pointer)
    void World::addObject(const std::shared_ptr<Shape>& object)
    {
        m_objects.push_back(object);
    }

    // World Intersection Calculator
    std::vector<Intersection> World::getIntersections(const Ray& ray) const
    {
        std::vector<Intersection> world_intersections{ };

        // Determine intersections for each object and aggregate into a single list
        for (const auto& object : m_objects) {
            std::vector<Intersection> object_intersections{ object->getIntersections(ray) };
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
        const auto possible_hit{ getHit(this->getIntersections(shadow_ray)) };

        // If the intersection occurs closer than the distance to the vector, the point is shadowed
        if (possible_hit && utils::isLess(possible_hit.value().getT(), light_source_displacement.magnitude())) {
            return true;
        }

        return false;
    }

    Color World::calculatePixelColor(const Ray& ray, const int remaining_bounces) const
    {
        // Get the list of intersections for the ray and check for a hit
        const std::vector<Intersection> world_intersections{ this->getIntersections(ray) };
        auto possible_hit{ getHit(world_intersections) };

        // Hit found calculate the color at that position
        if (possible_hit) {
            // Pre-compute values to utilize in shadow and reflection calculations
            const DetailedIntersection detailed_hit{ possible_hit.value(), ray };
            const bool is_shadowed{ this->isShadowed(detailed_hit.getOverPoint()) };
            const Color reflected_color{ this->calculateReflectedColor(detailed_hit, remaining_bounces) };

            // Calculate the surface color, and return the final value summed with the reflected color
            Color surface_color{ calculateSurfaceColor(detailed_hit.getObject(),
                                                       m_light_source,
                                                       detailed_hit.getOverPoint(),
                                                       detailed_hit.getSurfaceNormal(),
                                                       detailed_hit.getViewVector(),
                                                       is_shadowed) };
            return surface_color + reflected_color;
        }
        // No hit found, return black
        else {
            return black();
        }
    }

    Color World::calculateReflectedColor(const DetailedIntersection& intersection, const int remaining_bounces) const
    {
        // Bounce a ray to see what colors the reflective surface picks up
        const double object_reflectivity{ intersection.getObject().getMaterial().getReflectivity() };
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
}