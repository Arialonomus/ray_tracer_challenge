#pragma once

#include <memory>

#include "matrix3.hpp"
#include "color.hpp"
#include "vector3.hpp"

namespace gfx {
    class Texture
    {
    public:
        /* Constructors */

        // Default Constructor
        Texture() = default;

        // Standard Constructor
        explicit Texture(const Matrix3& transform_matrix)
                : m_transform{ transform_matrix }, m_transform_inverse{ transform_matrix.inverse() }
        {}

        /* Destructor */

        virtual ~Texture() = default;

        /* Accessors */

        [[nodiscard]] const Matrix3& getTransform() const
        { return m_transform; }

        // Returns the color at this texture's given uv coordinate
        [[nodiscard]] Color getTextureColorAt(const Vector3& uv_coordinate) const;

        /* Comparison Operator Overloads */

        [[nodiscard]] bool operator==(const Texture& rhs) const
        { return typeid(*this) == typeid(rhs) && areEquivalent(rhs); }

        /* Object Operations */

        // Creates a copy of this texture and returns a smart pointer to the new object
        [[nodiscard]] virtual std::shared_ptr<Texture> clone() const = 0;

    private:
        /* Data Members */

        Matrix3 m_transform{ };
        Matrix3 m_transform_inverse{ };

        /* Helper Methods */

        // Samples the texture at a UV coordinate that has been transformed using this texture's transform matrix
        [[nodiscard]] virtual Color sampleTextureAt(const Vector3& transformed_uv) const = 0;

        // Derived-class implemented equality check
        [[nodiscard]] virtual bool areEquivalent(const Texture& other_texture) const = 0;
    };
}
