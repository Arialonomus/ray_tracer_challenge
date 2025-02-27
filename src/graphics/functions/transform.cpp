#include "transform.hpp"

namespace gfx {
    // 2D Translation Matrix Factory Function (Float List Argument Overload)
    Matrix3 create2DTranslationMatrix(const double x, const double y)
    {
        return Matrix3{
                1.0, 0.0, x,
                0.0, 1.0, y,
                0.0, 0.0, 1.0
        };
    }

    // 2D Translation Matrix Factory Function (Vector3 Argument Overload)
    Matrix3 gfx::create2DTranslationMatrix(const Vector3& vec)
    {
        return Matrix3{
                1.0, 0.0, vec.x(),
                0.0, 1.0, vec.y(),
                0.0, 0.0, 1.0
        };
    }

    // 2D Scaling Matrix Factory Function (Float List Argument Overload)
    Matrix3 create2DScalingMatrix(const double x, const double y)
    {
        return Matrix3{
                x, 0.0, 0.0,
                0.0, y, 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Scaling Matrix Factory Function (Vector3 Argument Overload)
    Matrix3 create2DScalingMatrix(const Vector3& vec)
    {
        return Matrix3{
                vec.x(), 0.0, 0.0,
                0.0, vec.y(), 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Uniform Scaling Matrix Factory Function
    Matrix3 create2DScalingMatrix(const double scalar)
    {
        return Matrix3{
                scalar, 0.0, 0.0,
                0.0, scalar, 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Rotation Matrix Factory Function
    Matrix3 create2DRotationMatrix(const double angle)
    {
        return Matrix3{
                std::cos(angle), -std::sin(angle), 0.0,
                std::sin(angle), std::cos(angle), 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Horizontal Reflection Matrix Factory Function
    Matrix3 create2DHorizontalReflectionMatrix()
    {
        return Matrix3{
                1.0, 0.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Vertical Reflection Matrix Factory Function
    Matrix3 create2DVerticalReflectionMatrix()
    {
        return Matrix3{
                -1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Horizontal Skew Matrix Factory Function
    Matrix3 create2DHorizontalSkewMatrix(const double angle)
    {
        return Matrix3{
                1.0, std::tan(angle), 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
        };
    }

    // 2D Vertical Skew Matrix Factory Function
    Matrix3 create2DVerticalSkewMatrix(const double angle)
    {
        return Matrix3{
                1.0, 0.0, 0.0,
                std::tan(angle), 1.0, 0.0,
                0.0, 0.0, 1.0
        };
    }

    // Translation Matrix Factory Function (Float List Argument Overload)
    Matrix4 createTranslationMatrix(const double x, const double y, const double z)
    {
        return Matrix4{
                1.0, 0.0, 0.0, x,
                0.0, 1.0, 0.0, y,
                0.0, 0.0, 1.0, z,
                0.0, 0.0, 0.0, 1.0
        };
    }
    
    // Translation Matrix Factory Function (Vector4 Argument Overload)
    Matrix4 createTranslationMatrix(const Vector4& vec)
    {
        return Matrix4{
                1.0, 0.0, 0.0, vec.x(),
                0.0, 1.0, 0.0, vec.y(),
                0.0, 0.0, 1.0, vec.z(),
                0.0, 0.0, 0.0, 1.0
        };
    }
    
    // Scaling Matrix Factory Function (Float List Argument Overload)
    Matrix4 createScalingMatrix(const double x, const double y, const double z)
    {
        return Matrix4{
                x, 0.0, 0.0, 0.0,
                0.0, y, 0.0, 0.0,
                0.0, 0.0, z, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // Scaling Matrix Factory Function (Vector4 Argument Overload)
    Matrix4 createScalingMatrix(const Vector4& vec)
    {
        return Matrix4{
                vec.x(), 0.0, 0.0, 0.0,
                0.0, vec.y(), 0.0, 0.0,
                0.0, 0.0, vec.z(), 0.0,
                0.0, 0.0, 0.0, 1.0

        };
    }
    
    // Uniform Scaling Matrix Factory Function
    Matrix4 createScalingMatrix(const double scalar)
    {
        return Matrix4{
                scalar, 0.0, 0.0, 0.0,
                0.0, scalar, 0.0, 0.0,
                0.0, 0.0, scalar, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }
    
    // X-Axis Rotation Matrix Factory Function
    Matrix4 createXRotationMatrix(const double angle)
    {
        return Matrix4{
                1.0, 0.0, 0.0, 0.0,
                0.0, std::cos(angle), -std::sin(angle), 0.0,
                0.0, std::sin(angle), std::cos(angle), 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }
    
    // Y-Axis Rotation Matrix Factory Function
    Matrix4 createYRotationMatrix(const double angle)
    {
        return Matrix4{
                std::cos(angle), 0.0, sin(angle), 0.0,
                0.0, 1.0, 0.0, 0.0,
                -sin(angle), 0.0, std::cos(angle), 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }
    
    // Z-Axis Rotation Matrix Factory Function
    Matrix4 createZRotationMatrix(const double angle)
    {
        return Matrix4{
                std::cos(angle), -sin(angle), 0.0, 0.0,
                sin(angle), std::cos(angle), 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }
    
    // Skew Matrix Factory Function
    Matrix4 createSkewMatrix(
            const double x_y, const double x_z,
            const double y_x, const double y_z,
            const double z_x, const double z_y)
    {
        return Matrix4{
                1.0, x_y, x_z, 0.0,
                y_x, 1.0, y_z, 0.0,
                z_x, z_y, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
        };
    }

    // View Transform Matrix Factory Function
    Matrix4 createViewTransformMatrix(const Vector4& input_space, const Vector4& output_space, const Vector4& up_vector)
    {
        const Vector4 forward_vector{ normalize(output_space - input_space) };
        const Vector4 left_vector{ forward_vector.crossProduct(normalize(up_vector)) };
        const Vector4 true_up_vector{ left_vector.crossProduct(forward_vector) };

        const Matrix4 orientation{
            left_vector.x(), left_vector.y(), left_vector.z(), 0,
            true_up_vector.x(), true_up_vector.y(), true_up_vector.z(), 0,
            -forward_vector.x(), -forward_vector.y(), -forward_vector.z(), 0,
            0, 0, 0, 1
        };

        return orientation * createTranslationMatrix(-input_space);
    }
}