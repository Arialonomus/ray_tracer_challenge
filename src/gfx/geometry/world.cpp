#include "world.hpp"

#include <algorithm>

#include "shading_functions.hpp"

namespace gfx {
    // World Intersection Calculator
    std::vector<Intersection> World::getIntersections(const Ray& ray) const
    {
        std::vector<Intersection> world_intersections{ };

        // Determine intersections for each object and aggregate into a single list
        for (auto object_ref : m_objects) {
            auto object_intersections{ ray.getIntersections(object_ref.get()) };
            world_intersections.insert(world_intersections.end(),
                                       object_intersections.begin(),
                                       object_intersections.end());
        }

        // Sort list and return
        std::sort(world_intersections.begin(), world_intersections.end());
        return world_intersections;
    }

    Color World::calculatePixelColor(const Ray& ray) const
    {
        // Get the list of intersections for the ray and check for a hit
        const std::vector<Intersection> world_intersections{ this->getIntersections(ray) };
        auto possible_hit{ getHit(world_intersections) };

        // Hit found calculate the color at that position
        if (possible_hit) {
            const DetailedIntersection detailed_hit{ possible_hit.value(), ray };
            return calculateSurfaceColor(detailed_hit.getObject().getMaterial(),
                                         m_light_source,
                                         detailed_hit.getSurfacePosition(),
                                         detailed_hit.getSurfaceNormal(),
                                         detailed_hit.getViewVector());
        }
        // No hit found, return black
        else {
            return Color{ 0, 0, 0 };
        }
    }
}