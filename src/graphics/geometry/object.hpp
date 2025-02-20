#pragma once

#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Forward Declarations */
    class Ray;
    class Intersection;
    class Group;

    class Object
    {
    public:
        /* Constructors */

        // Default Constructor
        Object() = default;

        // Standard Constructor
        explicit Object(const Matrix4& transform)
                : m_transform{ transform }, m_parent{ nullptr }
        {}

        // Copy Constructor
        Object(const Object&) = default;

        /* Destructor */

        virtual ~Object() = default;

        /* Assignment Operators */

        Object& operator=(const Object&) = default;

        /* Accessors */

        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }

        [[nodiscard]] bool hasParent() const
        { return m_parent != nullptr; }

        [[nodiscard]] const Group* getParent() const
        { return m_parent; }

        /* Mutators */

        void setTransform(const Matrix4& transform_matrix)
        { m_transform = transform_matrix; }

        void setParent(Group* const parent_group_ptr)
        { m_parent = parent_group_ptr; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Object& rhs) const;

        /* Object Operations */

        [[nodiscard]] virtual std::shared_ptr<Object> clone() const = 0;

        /* Geometric Operations */

        // Returns the surface normal vector at a passed-in world_point
        [[nodiscard]] Vector4 getSurfaceNormalAt(const Vector4& world_point) const;

        // Returns a vector of Intersection objects representing the distances at which
        // the passed-in ray intersects with this object
        [[nodiscard]] std::vector<Intersection> getObjectIntersections(const Ray& ray) const;

    private:
        /* Data Members */

        Matrix4 m_transform{ gfx::createIdentityMatrix() };
        Group* m_parent{ nullptr };

        /* Helper Methods */

    protected:
        // Recursively transforms a point from its current space to the local space for this object,
        // ensuring transformations for each parent object are applied
        [[nodiscard]] Vector4 transformToObjectSpace(const Vector4& point) const;

        // Recursively transforms a normalized vector from an object's local space through its
        // parent's local spaces until the normal is in world space
        [[nodiscard]] Vector4 transformNormalToWorldSpace(const Vector4& local_normal) const;

    private:
        /* Pure Virtual Helper Methods */

        [[nodiscard]] virtual Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const = 0;
        [[nodiscard]] virtual std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const = 0;
        [[nodiscard]] virtual bool areEquivalent(const Object& other_object) const = 0;
    };

}
