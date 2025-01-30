#pragma once

#include <vector>
#include <memory>

#include "light.hpp"
#include "vector4.hpp"
#include "ray.hpp"
#include "intersection.hpp"

namespace gfx {
    class Shape;
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
        template<typename... ShapePtrs>
        explicit World(const std::shared_ptr<Shape>& first_object,
                       const ShapePtrs&... remaining_objects)
                : m_light_source{ Color{ 1, 1, 1 },
                                  createPoint(-10, 10, -10) },
                m_objects { first_object, remaining_objects...  }
        {}

        template<typename... ShapeRefs>
        explicit World(const Shape& first_object,
                       const ShapeRefs&... remaining_objects)
                : m_light_source{ Color{ 1, 1, 1 },
                                  createPoint(-10, 10, -10) }
        { addObjects(first_object, remaining_objects...); }

        // Standard Constructors
        template<typename... ShapePtrs>
        World(const PointLight& light_source,
              const std::shared_ptr<Shape>& first_object,
              const ShapePtrs&... remaining_objects)
                : m_light_source{ light_source },
                m_objects { first_object, remaining_objects...  }
        {}

        template<typename... ShapeRefs>
        World(const PointLight& light_source,
              const Shape& first_object,
              const ShapeRefs&... remaining_objects)
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

        [[nodiscard]] const Shape& getObjectAt(const size_t index) const
        { return *m_objects.at(index); }

        /* Mutators */

        // Adds a single object to the world
        void addObject(const Shape& object);
        void addObject(std::shared_ptr<Shape> object);

        /* Ray-Tracing Operations */

        // Returns a sorted list of all intersections with objects in this world with a passed-in Ray
        [[nodiscard]] std::vector<Intersection> getIntersections(const Ray& ray) const;

        // Returns true if the passed-in position is in shadow
        [[nodiscard]] bool isShadowed(const Vector4& point) const;

        // Returns the pixel color for the ray hit using pre-computed vector data for that point in world space
        [[nodiscard]] Color calculatePixelColor(const Ray& ray) const;

    private:
        /* Data Members */

        PointLight m_light_source{ Color{ 1, 1, 1 },
                                   createPoint(-10, 10, -10) };
        std::vector<std::shared_ptr<Shape>> m_objects{ };

        /* Helper Methods */

        // Add multiple objects passed in as references to the world
        template<typename... ShapeRefs>
        void addObjects(const Shape& first_object, const ShapeRefs&... remaining_objects) {
            this->addObject(first_object);
            addObjects(remaining_objects...);
        }
        void addObjects() {}    // Base case for recursion
    };
}
