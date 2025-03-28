#pragma once

#include "surface.hpp"

#include <vector>
#include <limits>

namespace gfx {
    class Cylinder : public Surface
    {
    public:
        /* Constructors */

        // Default Constructor (Unbounded Cylinder)
        Cylinder() = default;

        // Default Constructor (Bounded Cylinder)
        Cylinder(const double y_min, const double y_max, bool is_closed = false)
                : Surface{ },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Transform-Only Constructor (Unbounded Cylinder)
        explicit Cylinder(const Matrix4& transform)
                : Surface{ transform },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() },
                  m_is_closed{ false }
        {}

        // Transform-Only Constructor (Bounded Cylinder)
        Cylinder(const Matrix4& transform, const double y_min, const double y_max, bool is_closed = false)
                : Surface{ transform },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Material-Only Constructor (Unbounded Cylinder)
        explicit Cylinder(const Material& material)
                : Surface{ material },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() },
                  m_is_closed{ false }
        {}

        // Material-Only Constructor (Bounded Cylinder)
        Cylinder(const Material& material, const double y_min, const double y_max, bool is_closed = false)
                : Surface{ material },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Standard Constructor (Unbounded Cylinder)
        Cylinder(const Matrix4& transform, const Material& material)
                : Surface{ transform, material },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() },
                  m_is_closed{ false }
        {}

        // Standard Constructor (Bounded Cylinder)
        Cylinder(const Matrix4& transform,
                 const Material& material,
                 const double y_min,
                 const double y_max,
                 bool is_closed = false)
                : Surface{ transform, material },
                  m_y_min{ y_min },
                  m_y_max{ y_max },
                  m_is_closed{ is_closed }
        {}

        // Copy Constructor
        Cylinder(const Cylinder&) = default;

        /* Destructor */

        ~Cylinder() override = default;

        /* Assignment Operators */

        Cylinder& operator=(const Cylinder&) = default;

        /* Accessors */

        [[nodiscard]] double getYMin() const
        { return m_y_min; }

        [[nodiscard]] double getYMax() const
        { return m_y_max; }

        [[nodiscard]] bool isClosed() const
        { return m_is_closed; }

        [[nodiscard]] BoundingBox getBounds() const override
        { return BoundingBox{ -1, m_y_min, -1,
                              1, m_y_max, 1 }; }

        /* Mutators */

        // Adds a lower bound to the cylinder's local y-value
        void setYMin(const double y_min)
        { m_y_min = y_min; }

        // Removes the lower bound of the cylinder
        void unboundYMin()
        { m_y_min = -std::numeric_limits<double>::infinity(); }

        // Adds an upper bound to the cylinder's local y-value
        void setYMax(const double y_max)
        { m_y_max = y_max; }

        // Removes the upper bound of the cylinder
        void unboundYMax()
        { m_y_max = std::numeric_limits<double>::infinity(); }

        // Sets the upper and lower bound simultaneously
        void setCylinderBounds(const double y_min, const double y_max)
        {
            this->setYMin(y_min);
            this->setYMax(y_max);
        }

        // Removes upper and lower bounds from the cylinder height
        void unboundCylinder()
        {
            this->unboundYMin();
            this->unboundYMax();
        }

        // Adds end caps to a cylinder
        void capCylinder()
        { m_is_closed = true; }

        // Removes end caps from a cylinder
        void uncapCylinder()
        { m_is_closed = false; }

        /* Object Operations */

        // Creates a clone of this cylinder to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Object> clone() const override
        { return std::make_shared<Cylinder>(*this); }

    private:
        /* Data Members */

        double m_y_min{ -std::numeric_limits<double>::infinity() };
        double m_y_max{ std::numeric_limits<double>::infinity() };
        bool m_is_closed{ false };

        /* Shape Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;

        /* Object Helper Method Overrides */

        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
        [[nodiscard]] bool areEquivalent(const Object& other_object) const override;

        /* Cylinder Helper Methods */

        // Calculates the intersections with the end
        [[nodiscard]] std::vector<Intersection> calculateEndCapIntersections(const Ray& transformed_ray) const;

        // Returns true if a ray's position at t is within a radius of 1 from the y-axis
        [[nodiscard]] static bool isWithinCylinderWalls(const Ray& ray, double t) ;
    };
}
