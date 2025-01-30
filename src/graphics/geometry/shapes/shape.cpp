#include "shape.hpp"

namespace gfx {
    Vector4 Shape::getSurfaceNormal(const Vector4& world_point) const
    {
        // Transform the point from world space to object space
        const Matrix4 transform_inverse{ m_transform.inverse() };
        const Vector4 object_point{ transform_inverse * world_point };

        // Calculate the normal vector and transform back to world space
        const Vector4 object_normal{ this->calculateSurfaceNormal(object_point) };
        Vector4 world_normal{ transform_inverse.transpose() * object_normal };

        // Reset the w-value in case the shape's transformation matrix included a translation
        world_normal.resetW();

        // Normalize the world-space vector and return
        return normalize(world_normal);
    }

    std::vector<Intersection> Shape::getIntersections(const Ray& ray) const
    {
        // Transform the ray to the object space of the sphere
        const Ray transformed_ray{ ray.transform(m_transform.inverse()) };

        // Calculate the intersections for this shape and return
        return this->calculateIntersections(transformed_ray);
    }
}