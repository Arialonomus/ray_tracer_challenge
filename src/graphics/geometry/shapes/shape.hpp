#pragma once

#include <vector>

#include "matrix4.hpp"
#include "material.hpp"
#include "vector4.hpp"
#include "intersection.hpp"
#include "ray.hpp"

namespace gfx {
    class Shape
    {
    public:
        /* Constructors */
    
        Shape() = default;
        explicit Shape(const Matrix4& transform)
                : m_transform{ transform }, m_material{ }
        {}
        explicit Shape(const Material& material)
                : m_transform{ gfx::createIdentityMatrix() }, m_material{ material }
        {}
        Shape(const Matrix4& transform, const Material& material)
                : m_transform{ transform }, m_material{ material }
        {}
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
    
        /* Mutators */
    
        void setTransform(const Matrix4& transform_matrix)
        { m_transform = transform_matrix; }
        void setMaterial(const Material& material)
        { m_material = material; }
    
        /* Geometric Operations */
    
        // Returns the surface normal vector at a passed-in world_point
        [[nodiscard]] Vector4 getSurfaceNormal(const Vector4& world_point) const;

        // Returns a vector of Intersection objects representing the distances at which
        // the passed-in ray intersects with this shape
        [[nodiscard]] std::vector<Intersection> getIntersections(const Ray& ray) const;
    
    private:
        /* Data Members */

        Matrix4 m_transform{ gfx::createIdentityMatrix() };
        Material m_material{ };

        /* Pure Virtual Helper Methods */

        [[nodiscard]] virtual Vector4 calculateSurfaceNormal(const Vector4& transformed_point) const = 0;
        [[nodiscard]] virtual std::vector<Intersection> calculateIntersections(const Ray& transformed_ray) const = 0;
    };
}
