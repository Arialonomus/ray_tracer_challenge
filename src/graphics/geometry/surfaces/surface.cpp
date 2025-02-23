#include "surface.hpp"

#include "composite_surface.hpp"

namespace gfx {
    const Material& Surface::getMaterial() const
    {
        if (this->hasParent() && this->getParent()->hasMaterial())
            return this->getParent()->getMaterial();
        else
            return m_material;
    }

    Color Surface::getObjectColorAt(const Vector4& world_point) const
    {
        const Material& material{ this->getMaterial() };

        if (material.hasPattern()) {
            // Apply object and pattern transformations and sample the point
            const Vector4 object_point{ this->transformToObjectSpace(world_point) };
            const Vector4 pattern_point{ material.getPattern().getTransformInverse() * object_point };

            return material.getPattern().samplePatternAt(pattern_point);
        }

        // Return the base surface color
        return material.getColor();
    }

    Vector4 Surface::getSurfaceNormalAt(const Vector4& world_point) const
    {
        // Transform the point from world space to object space
        const Vector4 object_point{ this->transformToObjectSpace(world_point) };

        // Calculate the normal vector and transform back to world space for return
        const Vector4 object_normal{ this->calculateSurfaceNormal(object_point) };
        return this->transformNormalToWorldSpace(object_normal);
    }
}