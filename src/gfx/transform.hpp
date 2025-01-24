#pragma once

#include <cmath>

#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Transformation Matrix Factory Functions */

    // Returns a matrix representing a translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createTranslationMatrix(const float x, const float y, const float z)
    {
        return Matrix4{
                1.0, 0.0, 0.0, x,
                0.0, 1.0, 0.0, y,
                0.0, 0.0, 1.0, z,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a translation along the passed-in vector
    [[nodiscard]] Matrix4 createTranslationMatrix(const Vector4& vec)
    {
        return Matrix4{
                1.0, 0.0, 0.0, vec.x(),
                0.0, 1.0, 0.0, vec.y(),
                0.0, 0.0, 1.0, vec.z(),
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createScalingMatrix(const float x, const float y, const float z)
    {
        return Matrix4{
                x, 0.0, 0.0, 0.0,
                0.0, y, 0.0, 0.0,
                0.0, 0.0, z, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix4 createScalingMatrix(const Vector4& vec)
    {
        return Matrix4{
                vec.x(), 0.0, 0.0, 0.0,
                0.0, vec.y(), 0.0, 0.0,
                0.0, 0.0, vec.z(), 0.0,
                0.0, 0.0, 0.0, 1.0

        };
    }

    // Returns a matrix representing a rotation around the x-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createXRotationMatrix(const float angle)
    {
        return Matrix4{
                1.0, 0.0, 0.0, 0.0,
                0.0, std::cos(angle), -std::sin(angle), 0.0,
                0.0, std::sin(angle), std::cos(angle), 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a rotation around the y-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createYRotationMatrix(const float angle)
    {
        return Matrix4{
                std::cos(angle), 0.0, sin(angle), 0.0,
                0.0, 1.0, 0.0, 0.0,
                -sin(angle), 0.0, std::cos(angle), 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Returns a matrix representing a rotation around the z-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createZRotationMatrix(const float angle)
    {
        return Matrix4{
                std::cos(angle), -sin(angle), 0.0, 0.0,
                sin(angle), std::cos(angle), 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }
}