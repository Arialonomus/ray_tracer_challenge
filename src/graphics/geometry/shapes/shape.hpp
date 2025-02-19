#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "vector4.hpp"
#include "intersection.hpp"
#include "ray.hpp"

namespace gfx {
    // Forward Declarations
    class Ray;
    class Intersection;
    class Group;

    class Shape
    {
    public:
        /* Constructors */

        // Default Constructor
        Shape() = default;

        // Transform-Only Constructor
        explicit Shape(const Matrix4& transform)
                : m_transform{ transform }, m_material{ }, m_parent{ nullptr }
        {}

        // Material-Only Constructor
        explicit Shape(Material material)
                : m_transform{ gfx::createIdentityMatrix() }, m_material{ std::move(material) }, m_parent{ nullptr }
        {}

        // Standard Constructor
        Shape(const Matrix4& transform, Material material)
                : m_transform{ transform }, m_material{ std::move(material) }, m_parent{ nullptr }
        {}

        // Copy Constructor
        Shape(const Shape&) = default;

        /* Destructor */

        virtual ~Shape() = default;

        /* Assignment Operators */

        Shape& operator=(const Shape&) = default;

        /* Accessors */

        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }

        [[nodiscard]] const Material& getMaterial() const
        { return m_material; }

        [[nodiscard]] Color getObjectColorAt(const Vector4& world_point) const;

        [[nodiscard]] bool hasParent() const
        { return m_parent != nullptr; }

        [[nodiscard]] const Group* getParent() const
        { return m_parent; }

        /* Mutators */

        void setTransform(const Matrix4& transform_matrix)
        { m_transform = transform_matrix; }

        void setMaterial(const Material& material)
        { m_material = material; }

        void setParent(Group* const parent_group_ptr)
        { m_parent = parent_group_ptr; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Shape& rhs) const;

        /* Object Operations */

        [[nodiscard]] virtual std::shared_ptr<Shape> clone() const = 0;

        /* Geometric Operations */

        // Returns the surface normal vector at a passed-in world_point
        [[nodiscard]] Vector4 getSurfaceNormalAt(const Vector4& world_point) const;

        // Returns a vector of Intersection objects representing the distances at which
        // the passed-in ray intersects with this shape
        [[nodiscard]] std::vector<Intersection> getObjectIntersections(const Ray& ray) const;

    private:
        /* Data Members */

        Matrix4 m_transform{ gfx::createIdentityMatrix() };
        Material m_material{ };
        Group* m_parent{ nullptr };

        /* Pure Virtual Helper Methods */

        [[nodiscard]] virtual Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const = 0;
        [[nodiscard]] virtual std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const = 0;
        [[nodiscard]] virtual bool areEquivalent(const Shape& other_shape) const = 0;
    };
}
