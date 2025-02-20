#pragma once

#include "shape.hpp"

#include <vector>
#include <limits>

namespace gfx {
    class Cone : public Shape
    {
    public:
        /* Constructors */

        // Default Constructor (Unbounded Cone)
        Cone() = default;

        // Default Constructor (Bounded Cone)
        Cone(const double y_min, const double y_max, bool is_closed = false)
                : Shape{ },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Transform-Only Constructor (Unbounded Cone)
        explicit Cone(const Matrix4& transform)
                : Shape{ transform },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() },
                  m_is_closed{ false }
        {}

        // Transform-Only Constructor (Bounded Cone)
        Cone(const Matrix4& transform, const double y_min, const double y_max, bool is_closed = false)
                : Shape{ transform },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Material-Only Constructor (Unbounded Cone)
        explicit Cone(const Material& material)
                : Shape{ material },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() },
                  m_is_closed{ false }
        {}

        // Material-Only Constructor (Bounded Cone)
        Cone(const Material& material, const double y_min, const double y_max, bool is_closed = false)
                : Shape{ material },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Standard Constructor (Unbounded Cone)
        Cone(const Matrix4& transform, const Material& material)
                : Shape{ transform, material },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() },
                  m_is_closed{ false }
        {}

        // Standard Constructor (Bounded Cone)
        Cone(const Matrix4& transform,
                 const Material& material,
                 const double y_min,
                 const double y_max,
                 bool is_closed = false)
                : Shape{ transform, material },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Copy Constructor
        Cone(const Cone&) = default;

        /* Destructor */

        ~Cone() override = default;

        /* Assignment Operators */

        Cone& operator=(const Cone&) = default;

        /* Accessors */

        [[nodiscard]] double getYMin() const
        { return m_y_min; }

        [[nodiscard]] double getYMax() const
        { return m_y_max; }

        [[nodiscard]] bool isClosed() const
        { return m_is_closed; }

        /* Mutators */

        // Adds a lower bound to the cone's local y-value
        void setYMin(const double y_min)
        { m_y_min = y_min; }

        // Removes the lower bound of the cone
        void unboundYMin()
        { m_y_min = -std::numeric_limits<double>::infinity(); }

        // Adds an upper bound to the cone's local y-value
        void setYMax(const double y_max)
        { m_y_max = y_max; }

        // Removes the upper bound of the cone
        void unboundYMax()
        { m_y_max = std::numeric_limits<double>::infinity(); }

        // Sets the upper and lower bound simultaneously
        void setConeBounds(const double y_min, const double y_max)
        {
            this->setYMin(y_min);
            this->setYMax(y_max);
        }

        // Removes upper and lower bounds from the cone height
        void unboundCone()
        {
            this->unboundYMin();
            this->unboundYMax();
        }

        // Adds end caps to a cone
        void capCone()
        { m_is_closed = true; }

        // Removes end caps from a cone
        void uncapCone()
        { m_is_closed = false; }

        /* Object Operations */

        // Creates a clone of this cone to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Cone>(*this); }

    private:
        /* Data Members */

        double m_y_min{ -std::numeric_limits<double>::infinity() };
        double m_y_max{ std::numeric_limits<double>::infinity() };
        bool m_is_closed{ false };

        /* Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;

        /* Cone Helper Methods */

        // Calculates the intersections with the end
        [[nodiscard]] std::vector<Intersection> calculateEndCapIntersections(const Ray& transformed_ray) const;

        // Returns true if a ray's position at t is within the radius of the cone at a given y-position
        [[nodiscard]] static bool isWithinConeWalls(const Ray& ray, double t, double end_cap_y_val) ;
    };
}
