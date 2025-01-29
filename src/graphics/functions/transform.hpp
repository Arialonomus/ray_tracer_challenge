#pragma once

#include <cmath>

#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* Transformation Matrix Factory Functions */

    // Returns a matrix representing a translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createTranslationMatrix(double x, double y, double z);

    // Returns a matrix representing a translation along the passed-in vector
    [[nodiscard]] Matrix4 createTranslationMatrix(const Vector4& vec);

    // Returns a matrix representing a scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createScalingMatrix(double x, double y, double z);

    // Returns a matrix representing a uniform scaling by a factor of the passed-in scalar value
    [[nodiscard]] Matrix4 createScalingMatrix(double scalar);

    // Returns a matrix representing a scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix4 createScalingMatrix(const Vector4& vec);

    // Returns a matrix representing a rotation around the x-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createXRotationMatrix(double angle);

    // Returns a matrix representing a rotation around the y-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createYRotationMatrix(double angle);

    // Returns a matrix representing a rotation around the z-axis by the passed-in angle, in radians
    [[nodiscard]] Matrix4 createZRotationMatrix(double angle);

    // Returns a matrix representing a shearing/skew of each component in proportion to the other components
    [[nodiscard]] Matrix4 createSkewMatrix(
            double x_y, double x_z,
            double y_x, double y_z,
            double z_x, double z_y);

    // Returns a view transformation matrix representing a change of base from the input vector space to the output space
    [[nodiscard]] Matrix4 createViewTransformMatrix(
            const Vector4& input_space,
            const Vector4& output_space,
            const Vector4& up_vector);
}