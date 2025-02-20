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
}