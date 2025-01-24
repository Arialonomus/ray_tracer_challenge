#pragma once

#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Transformation Matrix Factory Functions */

    // Returns a matrix representing a translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 getTranslationMatrix(const float x, const float y, const float z)
    {
        return Matrix4{
                1.0, 0.0, 0.0, x,
                0.0, 1.0, 0.0, y,
                0.0, 0.0, 1.0, z,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a translation along the passed-in vector
    [[nodiscard]] Matrix4 getTranslationMatrix(const Vector4& vec)
    {
        return Matrix4{
                1.0, 0.0, 0.0, vec.x(),
                0.0, 1.0, 0.0, vec.y(),
                0.0, 0.0, 1.0, vec.z(),
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 getScalingMatrix(const float x, const float y, const float z)
    {
        return Matrix4{
                x, 0.0, 0.0, 0.0,
                0.0, y, 0.0, 0.0,
                0.0, 0.0, z, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix4 getScalingMatrix(const Vector4& vec)
    {
        return Matrix4{
                vec.x(), 0.0, 0.0, 0.0,
                0.0, vec.y(), 0.0, 0.0,
                0.0, 0.0, vec.z(), 0.0,
                0.0, 0.0, 0.0, 1.0

        };
    }
}