#include "transform.hpp"

// Translation Matrix Factory Function (Float List Argument Overload)
gfx::Matrix4 gfx::createTranslationMatrix(const float x, const float y, const float z)
{
    return gfx::Matrix4{
            1.0, 0.0, 0.0, x,
            0.0, 1.0, 0.0, y,
            0.0, 0.0, 1.0, z,
            0.0, 0.0, 0.0, 1.0
    };
}

// Translation Matrix Factory Function (Vector4 Argument Overload)
gfx::Matrix4 gfx::createTranslationMatrix(const gfx::Vector4& vec)
{
    return gfx::Matrix4{
            1.0, 0.0, 0.0, vec.x(),
            0.0, 1.0, 0.0, vec.y(),
            0.0, 0.0, 1.0, vec.z(),
            0.0, 0.0, 0.0, 1.0
    };
}

// Scaling Matrix Factory Function (Float List Argument Overload)
gfx::Matrix4 gfx::createScalingMatrix(const float x, const float y, const float z)
{
    return gfx::Matrix4{
            x, 0.0, 0.0, 0.0,
            0.0, y, 0.0, 0.0,
            0.0, 0.0, z, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

// Uniform Scaling Matrix Factory Function (Float Argument Overload)
gfx::Matrix4 gfx::createScalingMatrix(const float scalar)
{
    return gfx::Matrix4{
            scalar, 0.0, 0.0, 0.0,
            0.0, scalar, 0.0, 0.0,
            0.0, 0.0, scalar, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

// Scaling Matrix Factory Function (Vector4 Argument Overload)
gfx::Matrix4 gfx::createScalingMatrix(const gfx::Vector4& vec)
{
    return gfx::Matrix4{
            vec.x(), 0.0, 0.0, 0.0,
            0.0, vec.y(), 0.0, 0.0,
            0.0, 0.0, vec.z(), 0.0,
            0.0, 0.0, 0.0, 1.0

    };
}

// X-Axis Rotation Matrix Factory Function
gfx::Matrix4 gfx::createXRotationMatrix(const float angle)
{
    return gfx::Matrix4{
            1.0, 0.0, 0.0, 0.0,
            0.0, std::cos(angle), -std::sin(angle), 0.0,
            0.0, std::sin(angle), std::cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

// Y-Axis Rotation Matrix Factory Function
gfx::Matrix4 gfx::createYRotationMatrix(const float angle)
{
    return gfx::Matrix4{
            std::cos(angle), 0.0, sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(angle), 0.0, std::cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

// Z-Axis Rotation Matrix Factory Function
gfx::Matrix4 gfx::createZRotationMatrix(const float angle)
{
    return gfx::Matrix4{
            std::cos(angle), -sin(angle), 0.0, 0.0,
            sin(angle), std::cos(angle), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

// Skew Matrix Factory Function
gfx::Matrix4 gfx::createSkewMatrix(
        const float x_y, const float x_z,
        const float y_x, const float y_z,
        const float z_x, const float z_y)
{
    return gfx::Matrix4{
            1.0, x_y, x_z, 0.0,
            y_x, 1.0, y_z, 0.0,
            z_x, z_y, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}
