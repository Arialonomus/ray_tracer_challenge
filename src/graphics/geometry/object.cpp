#include "object.hpp"

#include "intersection.hpp"
#include "group.hpp"

namespace gfx {
    bool Object::operator==(const Object& rhs) const
    {
        if (typeid(*this) != typeid(rhs)) {
            return false;
        }
        return areEquivalent(rhs);
    }

    std::vector<Intersection> Object::getObjectIntersections(const Ray& ray) const
    {
        // Transform the ray to object space
        const Ray transformed_ray{ ray.transform(m_transform.inverse()) };

        // Calculate the intersections for this object and return
        return this->calculateIntersections(transformed_ray);
    }

    Vector4 Object::transformToObjectSpace(const Vector4& point) const
    {
        // Move up through the tree until the root object is found
        Vector4 transformed_point{ point };
        if (m_parent) {
            transformed_point = m_parent->transformToObjectSpace(transformed_point);
        }

        // Transform the point to object space and return
        return m_transform.inverse() * transformed_point;
    }

    Vector4 Object::transformNormalToWorldSpace(const Vector4& local_normal) const
    {
        // Transform the normal vector from local space to world space
        Vector4 world_normal{ m_transform.inverse().transpose() * local_normal };

        // Reset the w-value in case the shape's transformation matrix included a translation
        world_normal.resetW();
        world_normal = normalize(world_normal);

        // Recursively transform the normal through any parent object spaces in the tree
        if (m_parent) {
            world_normal = m_parent->transformNormalToWorldSpace(world_normal);
        }

        return world_normal;
    }
}