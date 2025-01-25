#pragma once

#include "matrix4.hpp"

namespace gfx {
    class Sphere
    {
    public:
        /* Constructors */

        Sphere() = default;
        Sphere(const Matrix4& transform)
                : m_transform{ transform }
        {}
        Sphere(const Sphere&) = default;
        Sphere(const Sphere&&) = default;

        /* Destructor */

        ~Sphere() = default;

        /* Assignment Operators */

        Sphere& operator=(const Sphere&) = default;
        Sphere& operator=(Sphere&&) = default;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Sphere& rhs) const;

        /* Accessors */

        // Returns the current transform matrix for this sphere
        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }

        /* Mutators */

        // Sets the transform of the sphere to equal that of the passed in transform matrix
        void setTransform(const Matrix4& transform_matrix)
        { m_transform = transform_matrix; }

    private:
        Matrix4 m_transform{ gfx::createIdentityMatrix() };
    };
}
