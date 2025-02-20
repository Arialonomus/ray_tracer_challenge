#pragma once

#include <vector>
#include <memory>

#include "light.hpp"
#include "vector4.hpp"
#include "ray.hpp"
#include "intersection.hpp"

namespace gfx {
    class Object;
    class Intersection;

    class World
    {
    public:
        /* Constructors */

        // Default Constructor
        World() = default;

        // Point Light Constructor
        explicit World(const PointLight& light_source);

        // Object List Constructors
        template<typename... ObjectPtrs>
        explicit World(const std::shared_ptr<Object>& first_object_ptr,
                       const ObjectPtrs&... remaining_object_ptrs)
                : m_light_source{ Color{ 1, 1, 1 },
                                  createPoint(-10, 10, -10) },
                m_objects { first_object_ptr, remaining_object_ptrs...  }
        {}

        template<typename... ObjectRefs>
        explicit World(const Object& first_object_ref,
                       const ObjectRefs&... remaining_object_refs)
                : m_light_source{ Color{ 1, 1, 1 },
                                  createPoint(-10, 10, -10) }
        { addObjects(first_object_ref, remaining_object_refs...); }

        // Standard Constructors
        template<typename... ObjectPtrs>
        World(const PointLight& light_source,
              const std::shared_ptr<Object>& first_object,
              const ObjectPtrs&... remaining_objects)
                : m_light_source{ light_source },
                m_objects { first_object, remaining_objects...  }
        {}

        template<typename... ObjectRefs>
        World(const PointLight& light_source,
              const Object& first_object,
              const ObjectRefs&... remaining_objects)
                : m_light_source{ light_source }
        { addObjects(first_object, remaining_objects...); }

        // Copy Constructor
        World(const World&) = default;

        // Move Constructor
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

        [[nodiscard]] const Object& getObjectAt(const size_t index) const
        { return *m_objects.at(index); }

        /* Mutators */

        // Adds a single object to the world
        void addObject(const Object& object);
        void addObject(const std::shared_ptr<Object>& object);

        /* Ray-Tracing Operations */

        // Returns a sorted list of all intersections with objects in this world with a passed-in Ray
        [[nodiscard]] std::vector<Intersection> getAllIntersections(const Ray& ray) const;

        // Returns true if the passed-in position is in shadow
        [[nodiscard]] bool isShadowed(const Vector4& point) const;

        // Returns the pixel color for the ray hit using pre-computed vector data for that point in world space
        [[nodiscard]] Color calculatePixelColor(const Ray& ray, int remaining_bounces = 5) const;

        // Returns the reflected color at a ray-object intersection
        [[nodiscard]] Color calculateReflectedColorAt(const DetailedIntersection& intersection,
                                                      int remaining_bounces = 5) const;

        // Returns the refracted color at a ray-object intersection
        [[nodiscard]] Color calculateRefractedColorAt(const DetailedIntersection& intersection,
                                                      const std::vector<Intersection>& possible_overlaps,
                                                      int remaining_bounces = 5) const;

    private:
        /* Data Members */

        PointLight m_light_source{ Color{ 1, 1, 1 },
                                   createPoint(-10, 10, -10) };
        std::vector<std::shared_ptr<Object>> m_objects{ };

        /* Helper Methods */

        // Add multiple objects passed in as references to the world
        template<typename... ObjectRefs>
        void addObjects(const Object& first_object, const ObjectRefs&... remaining_objects) {
            this->addObject(first_object);
            addObjects(remaining_objects...);
        }
        void addObjects() {}    // Base case for recursion
    };
}
