#pragma once

#include <vector>

#include "light.hpp"
#include "vector4.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "intersection.hpp"

namespace gfx {
    class World
    {
    public:
        /* Constructors */

        World() = default;
        explicit World(const PointLight& light_source)
                : m_light_source{ light_source },
                  m_objects{}
        {}
        template<typename... ObjectRefs>
        explicit World(const Sphere& first_object, const ObjectRefs&... remaining_objects)
                : m_light_source{ Color{ 1, 1, 1 },
                                  createPoint(-10, 10, -10) },
                  m_objects{ first_object, remaining_objects... }
        {}
        template<typename... ObjectRefs>
        World(const PointLight& light_source, const Sphere& first_object,
              const ObjectRefs&... remaining_objects)
                : m_light_source{ light_source },
                  m_objects{ first_object, remaining_objects... }
        {}
        World(World&) = default;
        World(World&&) = default;

        /* Destructor */

        ~World() = default;

        /* Assignment Operators */

        World& operator=(const World&) = default;
        World& operator=(World&&) = default;

        /* Accessors */

        [[nodiscard]] const PointLight& getLightSource() const
        { return m_light_source; }

        [[nodiscard]] size_t getObjectCount() const
        { return m_objects.size(); }

        [[nodiscard]] bool isEmpty() const
        { return m_objects.empty(); }

        [[nodiscard]] const Sphere& getObjectAt(const size_t index) const
        { return m_objects.at(index); }

        /* Mutators */

        void addObject(const Sphere& object)
        { m_objects.push_back(object); }

        /* Ray-Tracing Operations */

        // Returns a sorted list of all intersections with objects in this world with a passed-in Ray
        [[nodiscard]] std::vector<Intersection> getIntersections(const Ray& ray) const;

        // Returns the pixel color for the ray hit using pre-computed vector data for that point in world space
        [[nodiscard]] Color calculatePixelColor(const Ray& ray) const;

    private:
        PointLight m_light_source{ Color{ 1, 1, 1 },
                                   createPoint(-10, 10, -10) };
        std::vector<Sphere> m_objects{ };
    };
}
