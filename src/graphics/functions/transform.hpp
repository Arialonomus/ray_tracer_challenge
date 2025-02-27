#pragma once

#include <cmath>

#include "matrix3.hpp"
#include "vector3.hpp"
#include "matrix4.hpp"
#include "vector4.hpp"

namespace gfx {
    /* 2D Transformation Matrix Factory Functions */

    // Returns a matrix representing a 2D translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix3 create2DTranslationMatrix(double x, double y);

    // Returns a matrix representing a 2D translation along the passed-in vector
    [[nodiscard]] Matrix3 create2DTranslationMatrix(const Vector3& vec);

    // Returns a matrix representing a 2D scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix3 create2DScalingMatrix(double x, double y);

    // Returns a matrix representing a 2D scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix3 create2DScalingMatrix(const Vector3& vec);

    // Returns a matrix representing a uniform 2D scaling by a factor of the passed-in scalar value
    [[nodiscard]] Matrix3 create2DScalingMatrix(double scalar);

    // Returns a matrix representing a counterclockwise 2D rotation by the passed-in angle, in radians
    [[nodiscard]] Matrix3 create2DRotationMatrix(double angle);

    // Returns a matrix representing a 2D reflection across the x-axis
    [[nodiscard]] Matrix3 create2DHorizontalReflectionMatrix();

    // Returns a matrix representing a 2D reflection across the y-axis
    [[nodiscard]] Matrix3 create2DVerticalReflectionMatrix();

    // Returns a matrix representing a 2D skew along the x-axis
    [[nodiscard]] Matrix3 create2DHorizontalSkewMatrix(double angle);

    // Returns a matrix representing a 2D skew along the y-axis
    [[nodiscard]] Matrix3 create2DVerticalSkewMatrix(double angle);

    /* 3D Transformation Matrix Factory Functions */

    // Returns a matrix representing a translation along the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createTranslationMatrix(double x, double y, double z);

    // Returns a matrix representing a translation along the passed-in vector
    [[nodiscard]] Matrix4 createTranslationMatrix(const Vector4& vec);

    // Returns a matrix representing a scaling by a factor of the vector formed by passed-in coordinates
    [[nodiscard]] Matrix4 createScalingMatrix(double x, double y, double z);

    // Returns a matrix representing a scaling by a factor of the passed-in vector
    [[nodiscard]] Matrix4 createScalingMatrix(const Vector4& vec);

    // Returns a matrix representing a uniform scaling by a factor of the passed-in scalar value
    [[nodiscard]] Matrix4 createScalingMatrix(double scalar);

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