#pragma once

#include <cmath>

#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Transformation Matrix Factory Functions */

    // Returns a matrix representing a translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createTranslationMatrix(float x, float y, float z);

    // Returns a matrix representing a translation along the passed-in vector
    [[nodiscard]] Matrix4 createTranslationMatrix(const Vector4& vec);

    // Returns a matrix representing a scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createScalingMatrix(float x, float y, float z);

    // Returns a matrix representing a uniform scaling by a factor of the passed-in scalar value
    [[nodiscard]] Matrix4 createScalingMatrix(float scalar);

    // Returns a matrix representing a scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix4 createScalingMatrix(const Vector4& vec);

    // Returns a matrix representing a rotation around the x-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createXRotationMatrix(float angle);

    // Returns a matrix representing a rotation around the y-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createYRotationMatrix(float angle);

    // Returns a matrix representing a rotation around the z-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createZRotationMatrix(float angle);

    // Returns a matrix representing a shearing/skew of each component in proportion to the other components
    [[nodiscard]] Matrix4 createSkewMatrix(
            float x_y, float x_z,
            float y_x, float y_z,
            float z_x, float z_y);
}