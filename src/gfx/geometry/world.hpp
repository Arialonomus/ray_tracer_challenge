#pragma once

#include <vector>

#include "light.hpp"
#include "vector4.hpp"
#include "sphere.hpp"

namespace gfx {
    class World
    {
    public:
        /* Constructors */

        World() = default;
        explicit World(const PointLight& light_source )
                : m_light_source{ light_source },
                  m_objects{ }
        {}
        explicit World(const std::vector<std::reference_wrapper<Sphere>>& objects)
                : m_light_source{ Color{ 1, 1, 1 },
                                  createPoint(-10, 10, -10) },
                  m_objects{ objects }
        {}
        World(const PointLight& light_source, const std::vector<std::reference_wrapper<Sphere>>& objects)
                : m_light_source{ light_source },
                  m_objects{ objects }
        {}
        World(World&) = delete;
        World(World&&) = delete;

        /* Destructor */

        ~World() = default;

        /* Assignment Operators */

        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;

        /* Accessors */

        [[nodiscard]] const PointLight& getLightSource() const
        { return m_light_source; }

        [[nodiscard]] const std::vector<std::reference_wrapper<Sphere>>& getObjectList() const
        { return m_objects; }

    private:
        PointLight m_light_source{ Color{ 1, 1, 1 },
                                   createPoint(-10, 10, -10) };
        std::vector<std::reference_wrapper<Sphere>> m_objects{ };
    };
}
