#include "world.hpp"

#include <algorithm>

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
}