#pragma once

#include <memory>

#include "matrix4.hpp"
#include "color.hpp"
#include "vector4.hpp"

namespace gfx {
    class Pattern
    {
    public:
        /* Constructors */

        Pattern() = default;
        explicit Pattern(const Matrix4& transform_matrix)
                : m_transform{ transform_matrix }
        {}

        /* Destructor */

        virtual ~Pattern() = default;

        /* Accessors */

        [[nodiscard]] const Matrix4& getTransform() const
        { return m_transform; }

        [[nodiscard]] virtual Color getSurfaceColorAt(const Vector4& point) const = 0;

        /* Mutators */

        void setTransform(const Matrix4& transform_matrix)
        { m_transform = transform_matrix; }

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Pattern& rhs) const
        { return typeid(*this) == typeid(rhs) && equal(rhs); }

        /* Object Operations */

        [[nodiscard]] virtual std::unique_ptr<Pattern> clone() const = 0;

    private:
        /* Data Members */

        Matrix4 m_transform{ gfx::createIdentityMatrix() };

        /* Helper Methods */
        [[nodiscard]] virtual bool equal(const Pattern& other) const = 0;
    };
}
