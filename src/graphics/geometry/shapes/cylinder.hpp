#pragma once

#include "shape.hpp"

#include <vector>
#include <limits>

#include "matrix4.hpp"
#include "vector4.hpp"
#include "material.hpp"
#include "intersection.hpp"
#include "ray.hpp"

namespace gfx {
    class Cylinder : public Shape
    {
    public:
        /* Constructors */

        // Default Constructor (Unbounded Cylinder)
        Cylinder() = default;

        // Default Constructor (Bounded Cylinder)
        Cylinder(const double y_min, const double y_max)
                : Shape{ },
                  m_y_min{ y_min },
                  m_y_max{ y_max }
        {}

        // Transform-Only Constructor (Unbounded Cylinder)
        explicit Cylinder(const Matrix4& transform)
                : Shape{ transform },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() }
        {}

        // Transform-Only Constructor (Bounded Cylinder)
        Cylinder(const Matrix4& transform, const double y_min, const double y_max)
                : Shape{ transform },
                  m_y_min{ y_min },
                  m_y_max{ y_max }
        {}

        // Material-Only Constructor (Unbounded Cylinder)
        explicit Cylinder(const Material& material)
                : Shape{ material },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() }
        {}

        // Material-Only Constructor (Bounded Cylinder)
        Cylinder(const Material& material, const double y_min, const double y_max)
                : Shape{ material },
                  m_y_min{ y_min },
                  m_y_max{ y_max }
        {}

        // Standard Constructor (Unbounded Cylinder)
        Cylinder(const Matrix4& transform, const Material& material)
                : Shape{ transform, material },
                  m_y_min{ -std::numeric_limits<double>::infinity() },
                  m_y_max{ std::numeric_limits<double>::infinity() }
        {}

        // Standard Constructor (Bounded Cylinder)
        Cylinder(const Matrix4& transform, const Material& material, const double y_min, const double y_max)
                : Shape{ transform, material },
                  m_y_min{ y_min },
                  m_y_max{ y_max }
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

        /* Mutators */

        void setYMin(const double y_min)
        { m_y_min = y_min; }

        void uncapYMin()
        { m_y_min = -std::numeric_limits<double>::infinity(); }

        void setYMax(const double y_max)
        { m_y_max = y_max; }

        void uncapYMax()
        { m_y_max = std::numeric_limits<double>::infinity(); }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Cylinder& rhs) const;

        // Creates a clone of this cylinder to be stored in a world object list
        [[nodiscard]] std::shared_ptr<Shape> clone() const override
        { return std::make_shared<Cylinder>(*this); }

    private:
        /* Data Members */

        double m_y_min{ -std::numeric_limits<double>::infinity() };
        double m_y_max{ std::numeric_limits<double>::infinity() };

        /* Helper Method Overrides */

        [[nodiscard]] Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const override;
        [[nodiscard]] std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const override;
    };
}
