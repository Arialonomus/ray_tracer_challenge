#include "shape.hpp"

namespace gfx {
    Color Shape::getObjectColorAt(const Vector4& world_point) const
    {
        if (m_material.hasPattern()) {
            // Apply object and pattern transformations and sample the point
            const Vector4 object_point{ this->transformToObjectSpace(world_point) };
            const Vector4 pattern_point{ m_material.getPattern().getTransform().inverse() * object_point };

            return m_material.getPattern().samplePatternAt(pattern_point);
        }

        // Return the base surface color
        return m_material.getColor();
    }

    Vector4 Shape::getSurfaceNormalAt(const Vector4& world_point) const
    {
        // Transform the point from world space to object space
        const Vector4 object_point{ this->transformToObjectSpace(world_point) };

        // Calculate the normal vector and transform back to world space for return
        const Vector4 object_normal{ this->calculateSurfaceNormal(object_point) };
        return this->transformNormalToWorldSpace(object_normal);
    }
}