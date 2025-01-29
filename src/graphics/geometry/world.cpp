#include "world.hpp"

#include <algorithm>

#include "util_functions.hpp"
#include "shading_functions.hpp"

namespace gfx {
    // World Intersection Calculator
    std::vector<Intersection> World::getIntersections(const Ray& ray) const
    {
        std::vector<Intersection> world_intersections{ };

        // Determine intersections for each object and aggregate into a single list
        for (const Sphere& object : m_objects) {
            std::vector<Intersection> object_intersections{ ray.getIntersections(object) };
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

    Color World::calculatePixelColor(const Ray& ray) const
    {
        // Get the list of intersections for the ray and check for a hit
        const std::vector<Intersection> world_intersections{ this->getIntersections(ray) };
        auto possible_hit{ getHit(world_intersections) };

        // Hit found calculate the color at that position
        if (possible_hit) {
            // Pre-compute values to utilize in shadow and reflection calculations
            const DetailedIntersection detailed_hit{ possible_hit.value(), ray };
            const bool is_shadowed{ this->isShadowed(detailed_hit.getOverPoint()) };

            return calculateSurfaceColor(detailed_hit.getObject().getMaterial(),
                                         m_light_source,
                                         detailed_hit.getOverPoint(),
                                         detailed_hit.getSurfaceNormal(),
                                         detailed_hit.getViewVector(),
                                         is_shadowed);
        }
        // No hit found, return black
        else {
            return Color{ 0, 0, 0 };
        }
    }
}