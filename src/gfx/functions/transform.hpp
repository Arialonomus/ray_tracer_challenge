#pragma once

#include <cmath>

#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Transformation Matrix Factory Functions */

    // Returns a matrix representing a translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createTranslationMatrix(const float x, const float y, const float z);

    // Returns a matrix representing a translation along the passed-in vector
    [[nodiscard]] Matrix4 createTranslationMatrix(const Vector4& vec);

    // Returns a matrix representing a scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createScalingMatrix(const float x, const float y, const float z);

    // Returns a matrix representing a uniform scaling by a factor of the passed-in scalar value
    [[nodiscard]] Matrix4 createScalingMatrix(const float scalar);

    // Returns a matrix representing a scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix4 createScalingMatrix(const Vector4& vec);

    // Returns a matrix representing a rotation around the x-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createXRotationMatrix(const float angle);

    // Returns a matrix representing a rotation around the y-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createYRotationMatrix(const float angle);

    // Returns a matrix representing a rotation around the z-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createZRotationMatrix(const float angle);

    // Returns a matrix representing a shearing/skew of each component in proportion to the other components
    [[nodiscard]] Matrix4 createSkewMatrix(
            const float x_y, const float x_z,
            const float y_x, const float y_z,
            const float z_x, const float z_y);
}